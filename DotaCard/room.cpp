#include "room.h"
#include "dota.h"
#include <QDebug>
#include "net.h"

#include <QMessageBox>
#include "engine.h"
#include <QFile>
#include <QTextStream>
#include <QGraphicsSceneMouseEvent>

#define LeftPos QPointF(0,0)
#define RightPos QPointF(230,0)

#define DeckPos QPointF(745, 414)
#define HandPos QPointF(19+256, 529)
#define FieldyardPos QPointF(94+256, 317)
#define FieldgroundPos QPointF(94+256, 424)
#define GraveyardPos QPointF(485+256, 330)
#define EnemyDeckPos QPointF(5+256, 93)
#define EnemyHandPos QPointF(17+256, -71)
#define EnemyFieldyardPos QPointF(91+256, 213)
#define EnemyFieldgroundPos QPointF(91+256, 105)
#define EnemyGraveyardPos QPointF(15+256, 200)

//#define NoZValue 0
//#define DeckZValue 1
#define HandZValue 1
//#define FieldyardZValue 3
//#define SwordZValue 3.1
//#define FieldgroundZValue 4
//#define GraveyardZValue 5
//#define EnemyDeckZValue 6
#define EnemyHandZValue 1
//#define EnemyFieldyardZValue 8
//#define EnemyFieldgroundZValue 9
//#define EnemyGraveyardZValue 10

Room::Room(QObject* parent)
    : QGraphicsScene(parent)
{
    qNet->initialize();
    connect(qNet, SIGNAL(request_enemyDrawFirst()), this, SLOT(response_enemyDrawFirst()));
    connect(qNet, SIGNAL(request_enemySpecialSummon(QJsonObject)), this, SLOT(response_enemySpecialSummon(QJsonObject)));
    connect(qNet, SIGNAL(request_enemySummon(QJsonObject)), this, SLOT(response_enemySummon(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyActive(QJsonObject)), this, SLOT(response_enemyActive(QJsonObject)));
    connect(qNet, SIGNAL(request_enemySet(QJsonObject)), this, SLOT(response_enemySet(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyDeclared(QJsonObject)), this, SLOT(response_enemyDeclared(QJsonObject)));
    connect(qNet, SIGNAL(request_finishChain()), this, SLOT(response_finishChain()));
    connect(qNet, SIGNAL(request_destroyFieldyard(QJsonObject)), this, SLOT(response_destroyFieldyard(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyDestroyFieldyard(QJsonObject)), this, SLOT(response_enemyDestroyFieldyard(QJsonObject)));

    connect(qNet, SIGNAL(request_enemyChained(QJsonObject)), this, SLOT(response_enemyChained(QJsonObject)));

    connect(qNet, SIGNAL(request_setupDeck()), this, SLOT(response_setupDeck()));
    connect(qNet, SIGNAL(request_enemySetupDeck(QJsonObject)), this, SLOT(response_enemySetupDeck(QJsonObject)));
    connect(qNet, SIGNAL(request_startGame(QJsonObject)), this, SLOT(response_startGame(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyStartGame()), this, SLOT(response_enemyStartGame()));
    connect(qNet, SIGNAL(request_drawPhase()), this, SLOT(response_drawPhase()));
    connect(qNet, SIGNAL(request_standbyPhase()), this, SLOT(response_standbyPhase()));
    connect(qNet, SIGNAL(request_main1Phase()), this, SLOT(response_main1Phase()));
    connect(qNet, SIGNAL(request_endPhase()), this, SLOT(response_endPhase()));
    connect(qNet, SIGNAL(request_enemyDrawPhase()), this, SLOT(response_enemyDrawPhase()));
    connect(qNet, SIGNAL(request_enemyStandbyPhase()), this, SLOT(response_enemyStandbyPhase()));
    connect(qNet, SIGNAL(request_enemyMain1Phase()), this, SLOT(response_enemyMain1Phase()));
    connect(qNet, SIGNAL(request_enemyBattlePhase()), this, SLOT(response_enemyBattlePhase()));
    connect(qNet, SIGNAL(request_enemyMain2Phase()), this, SLOT(response_enemyMain2Phase()));
    connect(qNet, SIGNAL(request_enemyEndPhase()), this, SLOT(response_enemyEndPhase()));

    leftarea = new Pixmap(":/backdrop/left2");
    addItem(leftarea);
    leftarea->setPos(LeftPos);

    rightarea = new Pixmap(":/backdrop/right2");
    addItem(rightarea);
    rightarea->setPos(RightPos);

    bigImage = new Pixmap(":/image/NULL");
    bigImage->setParentItem(leftarea);
    bigImage->setPos(2,74);

    textedit = new QTextEdit;
    textedit->setFrameStyle(0);
    textedit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textedit->setStyleSheet("background-color: rgb(255, 240, 180);font-size:11pt;");

    textwidget = addWidget(textedit);
    textwidget->setPos(5,365);
    textwidget->resize(195,160);

    juedoukaishi = new Pixmap(":/png/duel_start");
    addItem(juedoukaishi);
    juedoukaishi->setPos(266,-242);

    connect(juedoukaishi, &Pixmap::finishedActionAnimation, [=](){ //决斗开始动画结束，开始抽5张卡
        juedoukaishi->hide();
        juedoukaishi->deleteLater();
//    music = new QSound("music/m_menu.wav");
//    music->stop();
//    music->play("music/start.wav");
//    music->play("music/m_duel1.wav");
        for (int i = 0; i < 5; ++i)
        {
            deckItems.first()->draw();
        }
        qNet->sendMessage(3000);
    });

    dp = new Phase("dp");
    addItem(dp);
    dp->setPos(221,82);

    sp = new Phase("sp");
    addItem(sp);
    sp->setPos(221,157);

    m1 = new Phase("m1");
    addItem(m1);
    m1->setPos(221,232);

    bp = new Phase("bp");
    addItem(bp);
    bp->setPos(221,307);
    connect(bp, &Phase::clicked, this, &Room::bp_clicked);

    m2 = new Phase("m2");
    addItem(m2);
    m2->setPos(221,382);
    connect(m2, &Phase::clicked, this, &Room::m2_clicked);

    ep = new Phase("ep");
    addItem(ep);
    ep->setPos(221,457);
    connect(ep, &Phase::clicked, this, &Room::ep_clicked);

    dp_pix = new Pixmap("phase_name/e_dr_b.png"); //抽卡流程
    addItem(dp_pix);
    dp_pix->setPos(383,278);
    dp_pix->hide();

    sp_pix = new Pixmap("phase_name/e_st_b.png"); //准备流程
    addItem(sp_pix);
    sp_pix->setPos(383,278);
    sp_pix->hide();

    m1_pix = new Pixmap("phase_name/e_m1_b.png"); //主要流程1
    addItem(m1_pix);
    m1_pix->setPos(383,278);
    m1_pix->hide();

    bp_pix = new Pixmap("phase_name/e_ba_b1.bmp");
    addItem(bp_pix);
    bp_pix->setPos(389, 278);
    bp_pix->hide();

    m2_pix = new Pixmap("phase_name/e_m2_b.png"); //主要流程2
    addItem(m2_pix);
    m2_pix->setPos(383,278);
    m2_pix->hide();

    ep_pix = new Pixmap("phase_name/e_en_b.png"); //结束流程
    addItem(ep_pix);
    ep_pix->setPos(383,278);
    ep_pix->hide();

    connect(dp_pix,&Pixmap::finishedChangePhaseAnimation, [=](){
        qDebug() << "hide_dp_pix finished";
        dp_pix->hide();
        qDota->phase = Dota::Draw_Phase;
        deckItems.first()->draw();
        qNet->sendMessage(10001);
    });

    connect(sp_pix,&Pixmap::finishedChangePhaseAnimation, [=](){ //准备流程动画结束后
        sp_pix->hide();
        qDota->phase = Dota::Standby_Phase;
        qDota->oneTurnOneNormalSummon = true;
        for (Card* card : qDota->allCards) //遍历所有卡牌，确保一回合一次，不会因为area变化而多次选发
        {
            card->standby();
        }
        qNet->sendMessage(20001);
    });

    connect(m1_pix,&Pixmap::finishedChangePhaseAnimation, [=](){
        m1_pix->hide();
        qDota->phase = Dota::Main1_Phase;
    //    //进入主要流程需要刷新鼠标手指样式
    //    for(Card* card : myHand)
    //    {
    //        card->changeFinger();
    //    }
    //    //我方进入主要流程，对方没有连锁点
        qNet->sendMessage(30001);
        qDota->whoIsDoing = true;
    });

    connect(bp_pix, &Pixmap::finishedEffect, this, [=](){
        bp_pix->hide();
        qDota->phase = Dota::Battle_Phase;
        //我方进入战斗流程，对方没有连锁点
        qNet->sendMessage(40001);
        qDota->whoIsDoing = true;
    });

    connect(m2_pix,&Pixmap::finishedChangePhaseAnimation, [=](){
        m2_pix->hide();
        qDota->phase = Dota::Main2_Phase;
        //我方进入主要流程，对方没有连锁点
        qNet->sendMessage(50001);
        qDota->whoIsDoing = true;
    });

    connect(ep_pix,&Pixmap::finishedChangePhaseAnimation, [=](){
        ep_pix->hide();
        qDota->phase = Dota::MyEnd_Phase;
        //我方进入结束流程，对方有连锁点
        qNet->sendMessage(60001);
        qDota->whoIsDoing = false;
    });

    //phase按钮翻转动画
    connect(dp,&Phase::finish, [=](){
        sp->effect();
    });
    connect(sp,&Phase::finish, [=](){
        m1->effect();
    });
    connect(m1,&Phase::finish, [=](){
        bp->effect();
    });
    connect(bp,&Phase::finish, [=](){
        m2->effect();
    });
    connect(m2,&Phase::finish, [=](){
        ep->effect();
    });

    for (int i = 0; i < 5; i++)
    {
        sword[i] = new Pixmap(":/png/sword");
        sword[i]->setPos(QPointF(80 * i, 0) + FieldyardPos);
        sword[i]->setZValue(3);
        addItem(sword[i]);
        sword[i]->hide();

        connect(sword[i], &Pixmap::finishedSwordAnimation, [=]() {
            sword[i]->hide();
            sword[i]->setPos(QPointF(80 * i, 0) + FieldyardPos);
            sword[i]->setRotation(0);

            //我方已经发动了战斗宣言。
            //发动卡片的效果吗？
            //You(Your opponent) have declared battle.
            //Activate the effect of a card?
            qDota->whoIsDoing = false; //什么都不能做，等待对方回应

        });
    }

    for (int j = 5; j < 10; j++)
    {
        sword[j] = new Pixmap(":/png/sword");
        sword[j]->setRotation(180);
        sword[j]->setPos(QPointF(320 - 80 * (j - 5), 0) + EnemyFieldyardPos);
        sword[j]->setZValue(3);
        addItem(sword[j]);
        sword[j]->hide();


        connect(sword[j], &Pixmap::finishedSwordAnimation, [=]() {
            sword[j]->hide();
            sword[j]->setPos(QPointF(320 - 80 * (j - 5), 0) + EnemyFieldyardPos);
            sword[j]->setRotation(180);

            bool can_chain = false;
            bool will_chain = false;
            for(int i=0; i<5; i++)
            {
                if(qDota->fieldyardCards[i]!=nullptr) //适用于对方战斗场合也能发动的怪兽效果
                {
                    if(qDota->fieldyardCards[i]->testEffectFromFieldyard() > 0)
                    {
                        can_chain = true;
                        break;
                    }
                }
                if(qDota->fieldgroundCards[i]!=nullptr)
                {
                    if(qDota->fieldgroundCards[i]->testEffectFromFieldground())
                    {
                        can_chain = true;
                        break;
                    }
                }
            }

            if(can_chain) //如果能连锁，请问你连不连锁
            {
                //“对方”已经发动了“战斗宣言”。“发动”卡片的效果吗？
                if(QMessageBox::Yes == QMessageBox::question(nullptr, "",
                                         QString(tr("Your opponent has declared battle.Activate the effect of a card")),
                                         QMessageBox::Yes, QMessageBox::No))
                {
                    qDota->whoIsDoing = true;
                    will_chain = true;

                    //只有确认连锁了，才需要指定连锁目标的类型
                    qDota->setSearchReason(Dota::ChainDeclared_Reason);
                    //还没选target就已经想好了原因，是连锁对方战斗宣言的
                }
            }

            if(!will_chain) //如果你不连锁，就告诉对方我不连锁
            {
                qDota->whoIsDoing = false;
                qNet->sendFinishChain();
            }

        });
    }

//    for (int k = 0; k < 5; k++)
//    {
//        word[k].setPos(90 + 78 * k+256, 390);
//        addItem(&word[k]);
//        word[k].setDefaultTextColor(Qt::white);
//        word[k].hide();
//    }

//    for (int l = 5; l < 10; l++)
//    {
//        word[l].setPos(402 - 78 * (l - 5)+256, 192);
//        addItem(&word[l]);
//        word[l].setDefaultTextColor(Qt::white);
//        word[l].hide();
//    }

    for(int i = 0; i < 5; ++i)
    {
        fieldyardItems[i] = nullptr;
        fieldgroundItems[i] = nullptr;
        enemyFieldyardItems[i] = nullptr;
        enemyFieldgroundItems[i] = nullptr;
    }

//    connect(FieldyardArea::instance(), &FieldyardArea::showWord, [=](int i) {
//        Card* card = FieldyardArea::instance()->getMyFieldyard().at(i);
//        int index = card->getIndex();
//        word[index].setPlainText(QString::number(card->getCurrentATK()).append("/ ").append(QString::number(card->getCurrentDEF())));
//        word[index].show();
//    });

//    connect(FieldyardArea::instance(), &FieldyardArea::hideWord, [=](int i) {
//        Card* card = FieldyardArea::instance()->getMyFieldyard().at(i);
//        int index = card->getIndex();
//        word[index].setPlainText("");
//        word[index].hide();
//    });

//    connect(EnemyFieldyardArea::instance(), &EnemyFieldyardArea::showWord, [=](int i) {
//        Card* card = EnemyFieldyardArea::instance()->getYourFieldyard().at(i);
//        int index = card->getIndex();
//        word[index + 5].setPlainText(QString::number(card->getCurrentATK()).append("/ ").append(QString::number(card->getCurrentDEF())));
//        word[index + 5].show();
//    });

//    connect(EnemyFieldyardArea::instance(), &EnemyFieldyardArea::hideWord, [=](int i) {
//        Card* card = EnemyFieldyardArea::instance()->getYourFieldyard().at(i);
//        int index = card->getIndex();
//        word[index + 5].setPlainText("");
//        word[index + 5].hide();
//    });

//    duifangxingdong = new GraphicsPixmapObject;
//    duifangxingdong->setPixmap(QPixmap(":/png/dfxd"));
//    addItem(duifangxingdong);
//    duifangxingdong->hide();

//    activeEffectCard = nullptr;

//    connect(Rule::instance(), &Rule::addMyLP, [=](int value) {
//        int myLP = ui->myNumber->intValue() + value;
//        ui->myLcdNumber->display(myLP);
//    });
//    connect(Rule::instance(), &Rule::addYourLP, [=](int value) {
//        int yourLP = ui->yourLcdNumber->intValue() + value;
//        ui->yourLcdNumber->display(yourLP);
//    });

    item_shine = new Pixmap(":/png/shine");
    item_shine->setZValue(5);
    item_shine->setPos(-500,-500);
    item_shine->setScale(0);
    item_shine->setOpacity(0);
    addItem(item_shine);

    item_enemy_shine = new Pixmap(":/png/shine");
    item_enemy_shine->setZValue(5);
    item_enemy_shine->setPos(-500,-500);
    item_enemy_shine->setScale(0);
    item_enemy_shine->setOpacity(0);
    addItem(item_enemy_shine);

    connect(item_shine, &Pixmap::finishedDoShineAnimation, [=]() {
        item_shine->setPos(-500,-500);
        item_shine->setScale(0);
        item_shine->setOpacity(0);

        Card* card = qDota->chainCard;
        int targetIndex = qDota->getCardIndexOfArea(card, card->getArea());
        int areaIndex = card->getArea();
        qNet->sendChained(targetIndex, areaIndex); // 考虑下提前发送Net连锁动画
    });

    connect(item_enemy_shine, &Pixmap::finishedDoShineAnimation, [=]() {
        item_enemy_shine->setPos(-500,-500);
        item_enemy_shine->setScale(0);
        item_enemy_shine->setOpacity(0);

//        bool can_chain = false;
        bool will_chain = false;
//        for(int i=0; i<5; i++)
//        {
//            if(qDota->fieldyardCards[i]!=NULL) //对方场上的item发动连锁，看看我方能不能连锁这个连锁
//            {
//                if(qDota->fieldyardCards[i]->testEffectFromFieldyard())
//                {
//                    can_chain = true;
//                    break;
//                }
//            }
//            if(qDota->fieldgroundCards[i]!=NULL)
//            {
//                if(qDota->fieldgroundCards[i]->testEffectFromFieldground())
//                {
//                    can_chain = true;
//                    break;
//                }
//            }
//        }

//        if(can_chain) //如果能连锁，请问你连不连锁
//        {
//            //“xxx”已发动。进行“连锁”吗？
//            if(QMessageBox::Yes == QMessageBox::question(0, "",
//                                     QString(tr("xxx is activated.Chain another card?")),
//                                     QMessageBox::Yes, QMessageBox::No))
//            {
//                qDota->whoIsDoing = true;
//                will_chain = true;

//                //只有确认连锁了，才需要指定连锁目标的类型
//                qDota->addAuthenticateCardArea(Card::Fieldyard_Area);
//                qDota->addAuthenticateCardArea(Card::Fieldground_Area);
//                qDota->searchTargetReason = Dota::ChainDeclared_Reason;
//            }
//        }

        if(!will_chain) //如果你不连锁，就告诉对方我不连锁
        {
            qDota->whoIsDoing = false;
            qNet->sendFinishChain();
        }
    });

}

////////////////////////////////////
///                              ///
///      Start    Here           ///
///                              ///
////////////////////////////////////

void Room::setupConnect(QList<Card*> list, bool enemy)
{
    for(Card* card : list)
    {
        CardItem *item = new CardItem(card);
        addItem(item);
        connect(item, &CardItem::hoverEnter, [=]() {
            QString name = item->getName();
            QString description = item->getDescription();
            bigImage->setPixmap(QString(":/image/%1").arg(name));
            //首先一张卡被hover，左上角大图肯定要更新
            //但对方的（除前后场的face-up卡）不该显示，我方卡组也不该显示
            bigImage->update();
            textedit->setText(description);
        });
        connect(item, &CardItem::beAttacked, [=]() {
            //无论表侧里侧，都可以选择作为目标target
            int sourceIndex = qDota->getCardIndexOfFieldyard(qDota->attackSourceCard); //主动攻击方
            int targetIndex = -1;
            QPointF p1 = sword[sourceIndex]->pos();
            QPointF p2 = QPointF(515, 0);
            if(qDota->hasEnemyMonster())
            {
                targetIndex = qDota->getCardIndexOfEnemyFieldyard(card); //被攻击方
                p2 = sword[5 + targetIndex]->pos();
            }
            else
            {
                qreal angle = QLineF(p2, p1).angleTo(QLineF(p2, p2 + QPointF(0, -1)));
                sword[sourceIndex]->setRotation(180 + angle);
            }

            sword[sourceIndex]->swordAnimation(p1, p2);
            qNet->sendDeclared(sourceIndex, targetIndex);
        });

        connect(item, &CardItem::chainDeclared, [=]() {
            qDebug() << "CardItem::chainDeclared" << item->pos();
            qDota->whoIsDoing = false;

            item_shine->setPos(item->pos() - QPoint(12,-1));
            item_shine->doShineAnimation();
        });

        connect(item, &CardItem::moveCardItem, [=](Card::AreaFlag from,Card::AreaFlag to){
            item->changeImage();
            switch (from)
            {
            case Card::Deck_Area:
                deckItems.removeOne(item);
                qDota->deckCards.removeOne(card);
                break;
            case Card::Hand_Area:
                handItems.removeOne(item);
                qDota->handCards.removeOne(card);
                adjustHandItems();
                break;
            case Card::Fieldyard_Area:
                fieldyardItems[qDota->getCardIndexOfFieldyard(card)] = nullptr;
                qDota->fieldyardCards[qDota->getCardIndexOfFieldyard(card)] = nullptr;
                break;
            case Card::Fieldground_Area:
                fieldgroundItems[qDota->getCardIndexOfFieldground(card)] = nullptr;
                qDota->fieldgroundCards[qDota->getCardIndexOfFieldground(card)] = nullptr;
                break;
            case Card::Graveyard_Area:
                graveyardItems.removeOne(item);
                break;
            case Card::EnemyDeck_Area:
                enemyDeckItems.removeOne(item);
                qDota->enemyHandCards.removeOne(card);
                break;
            case Card::EnemyHand_Area:
                enemyHandItems.removeOne(item);
                adjustEnemyHandItems();
                break;
            case Card::EnemyFieldyard_Area:
                enemyFieldyardItems[qDota->getCardIndexOfEnemyFieldyard(card)] = nullptr;
                qDota->enemyFieldyardCards[qDota->getCardIndexOfEnemyFieldyard(card)] = nullptr;
                break;
            case Card::EnemyFieldground_Area:
                enemyFieldgroundItems[qDota->getCardIndexOfEnemyFieldground(card)] = nullptr;
                qDota->enemyFieldgroundCards[qDota->getCardIndexOfEnemyFieldground(card)] = nullptr;
                break;
            case Card::EnemyGraveyard_Area:
                enemyGraveyardItems.removeOne(item);
                break;
            default:
                break;
            }
            switch (to)
            {
            case Card::Deck_Area:
                deckItems << item;
                item->setPos(DeckPos);
                item->setZValue(80-deckItems.size());
                qDota->deckCards << card;
                break;
            case Card::Hand_Area:
                handItems << item;
                adjustHandItems();
                qDota->handCards << card;
                break;
            case Card::Fieldyard_Area:
            {
                int index = testPlace(Card::Fieldyard_Area);
                fieldyardItems[index] = item;
                item->setPos(350+80*index, 317);
                item->setZValue(2);
                qDota->fieldyardCards[index] = card;
                break;
            }
            case Card::Fieldground_Area:
            {
                int index = testPlace(Card::Fieldground_Area);
                fieldgroundItems[index] = item;
                item->setPos(350+80*index, 424);
                item->setZValue(2);
                qDota->fieldgroundCards[index] = card;
                break;
            }
            case Card::Graveyard_Area:
                graveyardItems << item;
                item->setPos(GraveyardPos);
                qDota->graveyardCards << card;
                break;
            case Card::EnemyDeck_Area:
                enemyDeckItems << item;
                item->setPos(EnemyDeckPos);
                item->setZValue(80-enemyDeckItems.size());
                qDota->enemyDeckCards << card;
                break;
            case Card::EnemyHand_Area:
                enemyHandItems << item;
                adjustEnemyHandItems();
                qDota->enemyHandCards << card;
                break;
            case Card::EnemyFieldyard_Area:
            {
                int index = testPlace(Card::EnemyFieldyard_Area);
                enemyFieldyardItems[index] = item;
                item->setPos(EnemyFieldyardPos + QPointF(320 - 80 * index, 0));
                item->setZValue(2);
                qDota->enemyFieldyardCards[index] = card;
                break;
            }
            case Card::EnemyFieldground_Area:
            {
                int index = testPlace(Card::EnemyFieldground_Area);
                enemyFieldgroundItems[index] = item;
                item->setPos(EnemyFieldgroundPos + QPointF(320 - 80 * index, 0));
                item->setZValue(2);
                qDota->enemyFieldgroundCards[index] = card;
                break;
            }
            case Card::EnemyGraveyard_Area:
                enemyGraveyardItems << item;
                item->setPos(EnemyGraveyardPos);
                qDota->enemyGraveyardCards << card;
                break;
            default:
                break;
            }
        });
        if(enemy)
        {
            item->enemySetup();
        }
        else
        {
            item->setup();
        }
    }
}

void Room::adjustHandItems()
{
    if (handItems.isEmpty())
        return;
    int n = handItems.size();
    int card_skip = (n > 5) ? (412 / (n - 1)) : 102;
    for (int i = 0; i < n; i++)
    {
        handItems[i]->setZValue(HandZValue + 0.1 * i);
        handItems[i]->setPos(HandPos + QPointF(card_skip * i, 0));
    }
}

void Room::adjustEnemyHandItems()
{
    if (enemyHandItems.isEmpty())
        return;
    int n = enemyHandItems.size();
    int card_skip = (n > 5) ? (412 / (n - 1)) : 102;
    for (int i = 0; i < n; i++)
    {
        enemyHandItems[i]->setZValue(EnemyHandZValue + 0.1 * i);
        enemyHandItems[i]->setPos(EnemyHandPos + QPointF(408 - card_skip * i, 0));
    }
}

int Room::testPlace(Card::AreaFlag flag)
{
    for(int i = 0; i < 5; ++i)
    {
        if(flag == Card::Fieldyard_Area)
        {
            if(fieldyardItems[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::Fieldground_Area)
        {
            if(fieldgroundItems[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::EnemyFieldyard_Area)
        {
            if(enemyFieldyardItems[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::EnemyFieldground_Area)
        {
            if(enemyFieldgroundItems[i] == nullptr)
            {
                return i;
            }
        }
    }
    return -1;
}

void Room::response_enemyDrawFirst()
{
    enemyDeckItems.first()->response_drawFirst();
}

void Room::response_enemySpecialSummon(QJsonObject json)
{
    int index = json["index"].toInt();
    enemyHandItems[index]->response_specialSummon();
}

void Room::response_enemySummon(QJsonObject json)
{
    int index = json["index"].toInt();
    enemyHandItems[index]->response_summon();
}

void Room::response_enemyActive(QJsonObject json)
{
    int index = json["index"].toInt();
    enemyHandItems[index]->response_active();
}

void Room::response_enemySet(QJsonObject json)
{
    int index = json["index"].toInt();
    enemyHandItems[index]->response_set();
}

void Room::response_enemyDeclared(QJsonObject json)
{
    qDebug() << "response_enemyDeclared";
    int sourceIndex = json["sourceIndex"].toInt();
    int targetIndex = json["targetIndex"].toInt();

    qDota->attackSourceCard = qDota->enemyFieldyardCards[sourceIndex];
    qDota->attackDestinationCard = nullptr;

    QPointF p1 = sword[5 + sourceIndex]->pos();
    QPointF p2 = QPointF(515, height());

    if(targetIndex != -1)
    {
        p2 = sword[targetIndex]->pos();
        qDota->attackDestinationCard = qDota->fieldyardCards[targetIndex];
    }

    qreal angle = QLineF(p2, p1).angleTo(QLineF(p2, p2 + QPointF(0, -1)));
    sword[5 + sourceIndex]->setRotation(180 + angle);
    sword[5 + sourceIndex]->swordAnimation(p1, p2);

}

void Room::response_enemyChained(QJsonObject json)
{
    qDebug() << "response_enemyChained";
    int targetIndex = json["targetIndex"].toInt();
    int areaIndex = json["areaIndex"].toInt();
    CardItem *item = nullptr;

    if(areaIndex == Card::Fieldyard_Area)
    {
        item = enemyFieldyardItems[targetIndex];
    }
    else if(areaIndex == Card::Fieldground_Area)
    {
        item = enemyFieldgroundItems[targetIndex];
    }

    item_enemy_shine->setPos(item->pos() - QPoint(12,-1));
    item_enemy_shine->doShineAnimation();
}

//不连锁之后，发动卡牌效果一方执行连锁。
void Room::response_finishChain()
{
    qDebug() << "response_finishChain";
    if(qDota->chainStack.isEmpty())
    {
        return;
    }
    Dota::ReasonFlag flag = qDota->chainStack.pop();

    if(flag == Dota::ChainDeclared_Reason) // 这里应该有个while循环，response_finishChain();
    {
        qDota->chainCard->active();
        qDota->chainCard = nullptr;
    }
    else if(flag == Dota::BeAttacked_Reason)
    {
        //解锁中，不响应
        //先问自己是否连锁，再问对方是否连锁 /*简单处理下攻击后的伤亡情况*/
        int fieldyardIndex = qDota->getCardIndexOfFieldyard(qDota->attackSourceCard);
        int enemyFieldyardIndex = qDota->getCardIndexOfEnemyFieldyard(qDota->attackDestinationCard);
        fieldyardItems[fieldyardIndex]->battleSource();
        enemyFieldyardItems[enemyFieldyardIndex]->battleTarget();
        qDota->attackSourceCard = nullptr;
        qDota->attackDestinationCard = nullptr;
        qDota->whoIsDoing = true;
    }

    qNet->sendFinishChain(); //考虑下 最后一下可以不发

}

void Room::response_destroyFieldyard(QJsonObject json)
{
    qDebug() << "response_destroyFieldyard";
    int fieldyardIndex = json["index"].toInt();
    fieldyardItems[fieldyardIndex]->response_destroyFieldyard();
}

void Room::response_enemyDestroyFieldyard(QJsonObject json)
{
    qDebug() << "response_enemyDestroyFieldyard";
    int index = json["index"].toInt();
    enemyFieldyardItems[index]->response_enemyDestroyFieldyard();
//    qDota->sourceCard = nullptr;
}

void Room::bp_clicked()
{
    if(qDota->isSearchingTargetCard())
    {
        return;
    }
    if (qDota->phase == Dota::Main1_Phase)
    {
        //如果场上没怪，应该setDisable按钮
        //qDota->music->play("music/battle_turn.wav");

        //显示宝剑
        for (int i = 0; i<5; i++)
        {
            if(qDota->fieldyardCards[i] != nullptr)
            {
                if(qDota->fieldyardCards[i]->getFace() && qDota->fieldyardCards[i]->getStand())
                {
                    sword[i]->show();
                    //宝剑半透明还没做
                }
            }
        }

        //通知对方也显示宝剑和流程动画！

        //显示战斗流程渐入渐出动画
        bp_pix->show();
        bp_pix->effect();
    }
}

void Room::m2_clicked()
{
    if (qDota->phase == Dota::Battle_Phase)
    {
        m2_pix->setVisible(true);
        m2_pix->changePhaseAnimation(); //主要流程2的logo淡入淡出

        for (int i = 0; i<5; i++)
        {
            if(qDota->fieldyardCards[i] != nullptr)
            {
                sword[i]->hide();
            }
        }
    }
}

void Room::ep_clicked()
{
    if (qDota->phase == Dota::Battle_Phase)
    {
        for (int i = 0; i<5; i++)
        {
            if(qDota->fieldyardCards[i] != nullptr)
            {
                sword[i]->hide();
            }
        }
    }

    //应该从ep的 disable来设置点击后效果
    if (qDota->phase == Dota::Main1_Phase
        || qDota->phase == Dota::Battle_Phase
        || qDota->phase == Dota::Main2_Phase)
    {
        ep_pix->setVisible(true);
        ep_pix->changePhaseAnimation();
        //回合结束字样
        //闪动 end
    }
}

void Room::response_setupDeck()
{
    QVariantList allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QVariant(ISDN);
        Card* card = Engine::instance()->cloneCard(ISDN);
        qDota->allCards << card;
    }
    file.close();

    setupConnect(qDota->allCards, false);

//    for(Card* card : myAllCard)
//    {
//        myDeck << card;
//        card->setupCard();
//    }

    qNet->sendDeck(allISDN); //2000
}

void Room::response_enemySetupDeck(QJsonObject json)
{
    //先设置对方卡组
    QJsonArray array = json["array"].toArray();
    QVariantList list = array.toVariantList();
    for(QVariant value : list)
    {
        int ISDN = value.toInt();
        Card* card = Engine::instance()->cloneCard(ISDN);
        qDota->enemyAllCards << card;
    }

    setupConnect(qDota->enemyAllCards, true);

    for(Card* card : qDota->enemyAllCards)
    {
        qDota->enemyDeckCards << card;
        card->enemySetupCard();
    }

    //再设置自己卡组
    QVariantList allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QVariant(ISDN);
        Card* card = Engine::instance()->cloneCard(ISDN);
        qDota->allCards << card;
    }
    file.close();

    setupConnect(qDota->allCards, false);

    for(Card* card : qDota->allCards)
    {
        qDota->deckCards << card;
        card->setupCard();
    }

    qNet->sendEnemyDeck(allISDN); //2001
}

void Room::response_startGame(QJsonObject json)
{
    //先设置对方卡组
    QJsonArray array = json["array"].toArray();
    QVariantList list = array.toVariantList();
    for(QVariant value : list)
    {
        int ISDN = value.toInt();
        Card* card = Engine::instance()->cloneCard(ISDN);
        qDota->enemyAllCards << card;
    }

    setupConnect(qDota->enemyAllCards, true);

    for(Card* card : qDota->enemyAllCards)
    {
        qDota->enemyDeckCards << card;
        card->enemySetupCard();
    }

    //dota通知room决斗开始，绘制动画
    //决斗开始的字样从上到屏幕中央
    juedoukaishi->actionAnimation();
}

void Room::response_enemyStartGame()
{
    juedoukaishi->actionAnimation();
}

void Room::response_drawPhase()
{
    qDebug() << "response_drawPhase";
//    if(qDota->firstTurn)
//    {
//        qDota->firstTurn = false;
//        //渐入渐出动画 进入我方回合流程
//    }
    //隐藏对方行动字样
    //显示进入我方行动回合
    //全部phase切换成蓝色的动画
    //蓝色DP闪动
    //显示蓝色抽卡流程淡入淡出动画

    //后续修改动画，改成叠影动画
    dp_pix->setVisible(true);
    dp_pix->changePhaseAnimation();
}

void Room::response_standbyPhase()
{
    //隐藏对方行动字样
    //蓝色SP闪动
    //显示蓝色准备流程淡入淡出动画
    sp_pix->setVisible(true);
    sp_pix->changePhaseAnimation();
}

void Room::response_main1Phase()
{
    //蓝色M1闪动
    //显示蓝色抽卡流程淡入淡出动画
    m1_pix->setVisible(true);
    m1_pix->changePhaseAnimation();
}

void Room::response_endPhase()
{
    //隐藏对方行动字样
//    qDota->whoIsDoing = true;
//    DisCard from your hand. [NULL_mini] 手牌上限6张

    qDota->whoIsDoing = false;
    qNet->sendMessage(70001);
}

///////////////////////
///////////////////////
///////////////////////

void Room::chain(int number)
{
    bool can_do = false;
    for(int i=0; i<5; i++)
    {
//        if(qDota->myFieldyard[i]!=NULL)
//        {
//            if(qDota->myFieldyard[i]->testEffectFromFieldyard())
//            {
//                can_do = true;
//                break;
//            }
//        }
        if(qDota->fieldgroundCards[i]!=nullptr)
        {
            if(qDota->fieldgroundCards[i]->testEffectFromFieldground())
            {
                can_do = true;
                break;
            }
        }
    }

    if(can_do)
    {
        if(QMessageBox::question(nullptr, QString(tr("Warning")),
                                 QString(tr("Active Effect")),
                                 QMessageBox::Yes, QMessageBox::No)
                == QMessageBox::Yes)
        {
            qDota->whoIsDoing = true;
            return;
        }
    }

    qNet->sendMessage(number);
}

void Room::response_enemyDrawPhase() //client0收到client1说它进入了抽卡流程
{
    qDota->phase = Dota::EnemyDraw_Phase;
    //也要把对方的手牌显示出来

    //本来是蓝色EP在闪动
    //让我丢弃手牌
    //对方玩家回合蓝色渐变到红色，全部变成红色phase动画
    //红色DP在闪动
    //中间渐入渐出红色抽卡流程
    //弹出对话框问“进入对方的回合。发动卡片的效果吗？”
    chain(10002);
}

void Room::response_enemyStandbyPhase()
{
    qDota->phase = Dota::EnemyStandby_Phase;
    //初始化对方卡牌的standby函数

    //红色SP闪动
    //显示红色准备流程淡入淡出动画

    qDota->whoIsDoing = false;;
    qNet->sendMessage(20002);
}

void Room::response_enemyMain1Phase()
{
    qDota->phase = Dota::EnemyMain1_Phase;
    qDota->whoIsDoing = false;;
    //红色M1闪动
    //显示红色主要流程1淡入淡出动画
}

void Room::response_enemyBattlePhase()
{
    qDota->phase = Dota::EnemyBattle_Phase;
    qDota->whoIsDoing = false;;

    //显示宝剑
    for (int j = 0; j < 5; j++)
    {
        if(qDota->enemyFieldyardCards[j] != nullptr)
        {
            if(qDota->enemyFieldyardCards[j]->getFace() && qDota->enemyFieldyardCards[j]->getStand())
            {
                sword[j + 5]->show();
                //宝剑半透明还没做
            }
        }
    }
}

void Room::response_enemyMain2Phase()
{
    qDota->phase = Dota::EnemyMain2_Phase;
    qDota->whoIsDoing = false;;

    for (int j = 0; j < 5; j++)
    {
        if(qDota->enemyFieldyardCards[j] != nullptr)
        {
            sword[j + 5]->hide();
        }
    }

    //红色M2闪动
    //显示红色主要流程2淡入淡出动画
}

void Room::response_enemyEndPhase() //client1收到client0问是否连锁
{
    qDota->phase = Dota::EnemyEnd_Phase;

    for (int j = 0; j < 5; j++)
    {
        if(qDota->enemyFieldyardCards[j] != nullptr)
        {
            sword[j + 5]->hide();
        }
    }

    //本来是红色M2在闪动
    //上面显示蓝色对方行动

    //红色EP闪动
    //显示红色结束流程渐入渐出动画
    //弹出对话框问“对方将要结束回合。发动卡片的效果吗？”

    chain(60002);
}

void Room::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!qDota->whoIsDoing)
    {
        return QGraphicsScene::mousePressEvent(event);
    }
    if(qDota->getSearchReason()==Dota::BeAttacked_Reason
            && qDota->hasEnemyMonster()) //后续修改，屏蔽对方回合的响应,比如对方也在选target时
    {
        int index = qDota->getCardIndexOfFieldyard(qDota->attackSourceCard);
        QPointF p1 = sword[index]->pos() + QPointF(25, 36);
        QPointF p2 = sword[index]->pos() + QPointF(25, 0);
        QPointF p4 = event->scenePos();
        qreal angle = QLineF(p1, p4).angleTo(QLineF(p1, p2));
        sword[index]->setRotation(angle); //angle是弧度?
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Room::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(!qDota->whoIsDoing)
    {
        return QGraphicsScene::mousePressEvent(event);
    }
    if(qDota->getSearchReason()==Dota::BeAttacked_Reason
            && qDota->hasEnemyMonster())
    {
        if (event->button() == Qt::RightButton)
        {
            int index = qDota->getCardIndexOfFieldyard(qDota->attackSourceCard);
            sword[index]->setRotation(0);
            qDota->setSearchReason(Dota::No_Reason);
            qDota->attackSourceCard = nullptr; //默认 targetCard 肯定为null
        }
    }
    QGraphicsScene::mousePressEvent(event);
}
