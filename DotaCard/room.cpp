#include "room.h"
#include "dota.h"
#include <QDebug>

#include <QMessageBox>
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

Room::Room(QObject* parent)
    : QGraphicsScene(parent)
{
    qDota->initialize();
    connect(qDota, &Dota::createCardItem, this, &Room::createCardItem);
    connect(qDota, &Dota::createEnemyCardItem, this, &Room::createEnemyCardItem);
    connect(qDota, &Dota::moveCardItem, this, &Room::moveCardItem);

    connect(qDota, &Dota::goStartGame, this, &Room::goStartGame);
    connect(qDota, &Dota::goStandbyPhase, this, &Room::goStandbyPhase);
    connect(qDota, &Dota::goMain1Phase, this, &Room::goMain1Phase);
    connect(qDota, &Dota::goBattlePhase, this, &Room::goBattlePhase);
    connect(qDota, &Dota::goMain2Phase, this, &Room::goMain2Phase);
    connect(qDota, &Dota::goEndPhase, this, &Room::goEndPhase);
    connect(qDota, &Dota::goDrawPhase, this, &Room::goDrawPhase);

    connect(qDota, &Dota::showAttackAnimation, this, &Room::showAttackAnimation);
    connect(qDota, &Dota::showEnemyAttackAnimation, this, &Room::showEnemyAttackAnimation);
    connect(qDota, &Dota::showChainAnimation, this, &Room::showChainAnimation);
    connect(qDota, &Dota::showEquipAnimation, this, &Room::showEquipAnimation);
    connect(qDota, &Dota::showEquipHoverAnimation, this, &Room::showEquipHoverAnimation);
    connect(qDota, &Dota::hideEquipHoverAnimation, this, &Room::hideEquipHoverAnimation);

    connect(qDota, &Dota::showInfoDialog, this, &Room::showInfoDialog);
    connect(qDota, &Dota::showWarningDialog, this, &Room::showWarningDialog);

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

        qDota->goStartPhase();
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
    connect(bp, &Phase::clicked, [=](){
        //如果场上没怪，应该setDisable按钮
        //qDota->music->play("music/battle_turn.wav");
        qDota->tryGoBattlePhase();
    });

    m2 = new Phase("m2");
    addItem(m2);
    m2->setPos(221,382);
    connect(m2, &Phase::clicked, [=](){
        qDota->tryGoMain2Phase();
    });

    ep = new Phase("ep");
    addItem(ep);
    ep->setPos(221,457);
    connect(ep, &Phase::clicked, [=](){
        qDota->tryGoEndPhase();
    });

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
        });

        equipFieldyard[i] = new Pixmap(":/png/zhuangbeika");
        equipFieldyard[i]->setPos(QPointF(80 * i, 0) + FieldyardPos + QPoint(0,12));
        equipFieldyard[i]->setZValue(4);
        addItem(equipFieldyard[i]);
        equipFieldyard[i]->hide();

        equipFieldground[i] = new Pixmap(":/png/zhuangbeika");
        equipFieldground[i]->setPos(QPointF(80 * i, 0) + FieldgroundPos + QPoint(0,12));
        equipFieldground[i]->setZValue(4);
        addItem(equipFieldground[i]);
        equipFieldground[i]->hide();
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
        });

        equipFieldyard[j] = new Pixmap(":/png/zhuangbeika");
        equipFieldyard[j]->setPos(QPointF(320 - 80 * (j - 5), 0) + EnemyFieldyardPos + QPoint(0,12));
        equipFieldyard[j]->setZValue(4);
        addItem(equipFieldyard[j]);
        equipFieldyard[j]->hide();

        equipFieldground[j] = new Pixmap(":/png/zhuangbeika");
        equipFieldground[j]->setPos(QPointF(320 - 80 * (j - 5), 0) + EnemyFieldgroundPos + QPoint(0,12));
        equipFieldground[j]->setZValue(4);
        addItem(equipFieldground[j]);
        equipFieldground[j]->hide();
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

    item_shine = new Pixmap(":/png/shine");
    item_shine->setZValue(5);
    item_shine->setPos(-500,-500);
    item_shine->setScale(0);
    item_shine->setOpacity(0);
    addItem(item_shine);

    connect(item_shine, &Pixmap::finishedDoShineAnimation, [=]() {
        item_shine->setPos(-500,-500);
        item_shine->setScale(0);
        item_shine->setOpacity(0);
    });

    dialog = new InfoDialog(":/png/dialog");
    addItem(dialog);
    dialog->setZValue(7);
    dialog->hide();
    connect(dialog, &InfoDialog::clicked_ok, [=](){
        dialog->hide();
        qDota->setSearchReason(Dota::BeEquiped_Reason);
    });

    dialog2 = new WarningDialog(":/png/teshuzhaohuan");
    addItem(dialog2);
    dialog2->setZValue(7);
    dialog2->hide();
    connect(dialog2, &WarningDialog::clicked_yes, [=](){
        dialog2->hide();
        qDota->whoIsDoing = true;
        qDota->currentActiveCard->doActive();
        //show scroll area
    });
    connect(dialog2, &WarningDialog::clicked_no, [=](){
        dialog2->hide();
        qDota->whoIsDoing = true;
        qDota->currentActiveCard->unActive();
    });
}

void Room::showAttackAnimation(int sourceIndex, int targetIndex)
{
    QPointF p1 = sword[sourceIndex]->pos();
    QPointF p2 = QPointF(515, 0);
    if(targetIndex != -1)
    {
        p2 = sword[5 + targetIndex]->pos();
    }
    else
    {
        qreal angle = QLineF(p2, p1).angleTo(QLineF(p2, p2 + QPointF(0, -1)));
        sword[sourceIndex]->setRotation(180 + angle);
    }

    sword[sourceIndex]->swordAnimation(p1, p2);
}

void Room::showEnemyAttackAnimation(int sourceIndex, int targetIndex)
{
    QPointF p1 = sword[5 + sourceIndex]->pos();
    QPointF p2 = QPointF(515, height());

    if(targetIndex != -1)
    {
        p2 = sword[targetIndex]->pos();
    }

    qreal angle = QLineF(p2, p1).angleTo(QLineF(p2, p2 + QPointF(0, -1)));
    sword[5 + sourceIndex]->setRotation(180 + angle);
    sword[5 + sourceIndex]->swordAnimation(p1, p2);
}

CardItem *Room::getCardItemFromIndex(int targetIndex, int areaIndex)
{
    if (areaIndex == 3) //Fieldyard_Area
    {
        return fieldyardItems[targetIndex];
    }
    else if (areaIndex == 4) //Fieldground_Area
    {
        return fieldgroundItems[targetIndex];
    }
    else if (areaIndex == 8) //EnemyFieldyard_Area
    {
        return enemyFieldyardItems[targetIndex];
    }
    else if (areaIndex == 9) //EnemyFieldground_Area
    {
        return enemyFieldgroundItems[targetIndex];
    }
    else
    {
        return nullptr;
    }
}

void Room::showEquipAnimation(int from, int to)
{
    CardItem *itemFrom = getCardItemFromIndex(from, 4);
    CardItem *itemTo = getCardItemFromIndex(to, 3);
    Pixmap *pixmapItem = new Pixmap(itemFrom->pixmap());
    QPointF positionFrom = itemFrom->pos();
    QPointF positionTo = itemTo->pos();
    pixmapItem->setPos(positionFrom);
    pixmapItem->setZValue(66);
    addItem(pixmapItem);
    pixmapItem->doEquipAnimation(positionFrom, positionTo);
    connect(pixmapItem, &Pixmap::finishedEquipAnimation, [=](){
        pixmapItem->deleteLater();
        qDota->effectEquipSpellCard();
    });
}

void Room::showEquipHoverAnimation(int targetIndex, int areaIndex)
{
    if(areaIndex==3)
    {
        equipFieldyard[targetIndex]->show();
        equipFieldyard[targetIndex]->doEquipHoverAnimation();
    }
    if(areaIndex==4)
    {
        equipFieldground[targetIndex]->show();
        equipFieldground[targetIndex]->doEquipHoverAnimation();
    }
}

void Room::hideEquipHoverAnimation(int targetIndex, int areaIndex)
{
    if(areaIndex==3)
    {
        equipFieldyard[targetIndex]->hide();
        equipFieldyard[targetIndex]->doneEquipHoverAnimation();
    }
    if(areaIndex==4)
    {
        equipFieldground[targetIndex]->hide();
        equipFieldground[targetIndex]->doneEquipHoverAnimation();
    }
}

void Room::showChainAnimation(int targetIndex, int areaIndex)
{
    CardItem *item = getCardItemFromIndex(targetIndex, areaIndex);
    item_shine->setPos(item->pos() - QPoint(12,-1));
    item_shine->doShineAnimation();
    connect(item_shine, &Pixmap::finishedDoShineAnimation, [=](){
        qDota->afterActiveSpellCard(targetIndex, areaIndex);
    });
}

void Room::showInfoDialog()
{
    dialog->show();
    dialog->showAnimation();
}

void Room::showWarningDialog()
{
    dialog2->show();
    dialog2->showAnimation();
}

void Room::hoverEnter()
{
    CardItem *item = qobject_cast<CardItem *>(sender());
    bigImage->setPixmap(QString(":/image/%1").arg(item->getName()));
    //首先一张卡被hover，左上角大图肯定要更新
    //但对方的（除前后场的face-up卡）不该显示，我方卡组也不该显示
    bigImage->update();
    textedit->setText(item->getDescription());
}

void Room::createCardItem(int index)
{
    CardItem *item = new CardItem(qDota->getCardFromIndex(index));
    addItem(item);
    deckItems << item;
    item->setPos(DeckPos);
    item->setZValue(80-deckItems.size());

    connect(item, &CardItem::hoverEnter, this, &Room::hoverEnter);
}

void Room::createEnemyCardItem(int index)
{
    CardItem *item = new CardItem(qDota->getEnemyCardFromIndex(index));
    addItem(item);
    enemyDeckItems << item;
    item->setPos(EnemyDeckPos);
    item->setZValue(80-enemyDeckItems.size());

    connect(item, &CardItem::hoverEnter, this, &Room::hoverEnter);
}

void Room::moveCardItem(CardMoveStruct move)
{
    CardItem *item = nullptr;
    int indexFrom = move.indexFrom;
    int indexTo = move.indexTo;

    switch (move.areaFrom)
    {
    case Card::Deck_Area:
        item = deckItems.takeAt(indexFrom);
        break;
    case Card::Hand_Area:
        item = handItems.takeAt(indexFrom);
        adjustHandItems();
        break;
    case Card::Fieldyard_Area:
        item = fieldyardItems[indexFrom];
        fieldyardItems[indexFrom] = nullptr;
        break;
    case Card::Fieldground_Area:
        item = fieldgroundItems[indexFrom];
        fieldgroundItems[indexFrom] = nullptr;
        break;
    case Card::Graveyard_Area:
        item = graveyardItems.takeAt(indexFrom);
        break;

    case Card::EnemyDeck_Area:
        item = enemyDeckItems.takeAt(indexFrom);
        break;
    case Card::EnemyHand_Area:
        item = enemyHandItems.takeAt(indexFrom);
        adjustEnemyHandItems();
        break;
    case Card::EnemyFieldyard_Area:
        item = enemyFieldyardItems[indexFrom];
        enemyFieldyardItems[indexFrom] = nullptr;
        break;
    case Card::EnemyFieldground_Area:
        item = enemyFieldgroundItems[indexFrom];
        enemyFieldgroundItems[indexFrom] = nullptr;
        break;
    case Card::EnemyGraveyard_Area:
        item = enemyGraveyardItems.takeAt(indexFrom);
        break;
    default:
        // for No_Area
        break;
    }

    item->changeImage(); // Todo: 改到card里
    item->clearFinger(); // Todo: 改到card里

    switch (move.areaTo)
    {
    case Card::Deck_Area:
        deckItems << item;
        item->setPos(DeckPos);
        item->setZValue(80-deckItems.size());
        break;
    case Card::Hand_Area:
        handItems << item;
        adjustHandItems();
        break;
    case Card::Fieldyard_Area:
    {
        fieldyardItems[indexTo] = item;
        item->setPos(350+80*indexTo, 317);
        item->setZValue(2);
        break;
    }
    case Card::Fieldground_Area:
    {
        fieldgroundItems[indexTo] = item;
        item->setPos(350+80*indexTo, 424);
        item->setZValue(2);
        break;
    }
    case Card::Graveyard_Area:
        graveyardItems << item;
        item->setPos(GraveyardPos);
        item->setZValue(graveyardItems.size());
        break;
    case Card::EnemyDeck_Area:
        enemyDeckItems << item;
        item->setPos(EnemyDeckPos);
        item->setZValue(80-enemyDeckItems.size());
        break;
    case Card::EnemyHand_Area:
        enemyHandItems << item;
        adjustEnemyHandItems();
        break;
    case Card::EnemyFieldyard_Area:
    {
        enemyFieldyardItems[indexTo] = item;
        item->setPos(EnemyFieldyardPos + QPointF(320 - 80 * indexTo, 0));
        item->setZValue(2);
        break;
    }
    case Card::EnemyFieldground_Area:
    {
        enemyFieldgroundItems[indexTo] = item;
        item->setPos(EnemyFieldgroundPos + QPointF(320 - 80 * indexTo, 0));
        item->setZValue(2);
        break;
    }
    case Card::EnemyGraveyard_Area:
        enemyGraveyardItems << item;
        item->setPos(EnemyGraveyardPos);
        item->setZValue(enemyGraveyardItems.size());
        break;
    default:
        // for No_Area
        break;
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
        handItems[i]->setZValue(1 + 0.1 * i);
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
        enemyHandItems[i]->setZValue(1 + 0.1 * i);
        enemyHandItems[i]->setPos(EnemyHandPos + QPointF(408 - card_skip * i, 0));
    }
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
        int index = qDota->getCardIndex(qDota->attackSourceCard);
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
    if(qDota->getSearchReason()==Dota::BeAttacked_Reason && qDota->hasEnemyMonster())
    {
        if (event->button() == Qt::RightButton)
        {
            int index = qDota->getCardIndex(qDota->attackSourceCard);
            sword[index]->setRotation(0);
            qDota->setSearchReason(Dota::No_Reason);
            qDota->attackSourceCard = nullptr; //默认 targetCard 肯定为null
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Room::hideSwords()
{
    for (int i = 0; i<5; i++)
    {
        sword[i]->hide();
    }
}

void Room::goStartGame()
{
    //dota通知room决斗开始，绘制动画
    //决斗开始的字样从上到屏幕中央
    juedoukaishi->actionAnimation();
}

void Room::goDrawPhase() // TODO: 好像没人使用这个函数
{
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

void Room::goStandbyPhase()
{
    //隐藏对方行动字样
    //蓝色SP闪动
    //显示蓝色准备流程淡入淡出动画
    sp_pix->setVisible(true);
    sp_pix->changePhaseAnimation();
}

void Room::goMain1Phase()
{
    //蓝色M1闪动
    //显示蓝色抽卡流程淡入淡出动画
    m1_pix->setVisible(true);
    m1_pix->changePhaseAnimation();
}

void Room::goBattlePhase(QList<int> list)
{
    for(int i : list)
    {
        //显示宝剑
        sword[i]->show();
        //宝剑半透明还没做
    }

    //通知对方也显示宝剑和流程动画！

    //显示战斗流程渐入渐出动画
    bp_pix->effect();
}

void Room::goMain2Phase()
{
    hideSwords();

    m2_pix->setVisible(true);
    m2_pix->changePhaseAnimation(); //主要流程2的logo淡入淡出
}

void Room::goEndPhase()
{
    //不管有没有 sword
    hideSwords();
    //应该从ep的 disable来设置点击后效果

    ep_pix->setVisible(true);
    ep_pix->changePhaseAnimation();
    //回合结束字样
    //闪动 end
}
