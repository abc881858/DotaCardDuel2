#include "carditem.h"
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QImage>
#include <QPainter>
#include <QCursor>
#include "dota.h"
#include "engine.h"
#include "net.h"

//修改下面几个变量至头文件
#define cursorNoFlag QCursor(QPixmap(":/cursor/cur3"), 31, 15)
#define cursorEffect QCursor(QPixmap(":/cursor/cur4"), 15, 19)
#define cursorSpecialSummon QCursor(QPixmap(":/cursor/cur5"), 8, 26)
#define cursorNormalSummon QCursor(QPixmap(":/cursor/cur1"), 13, 19)
#define cursorSetCard QCursor(QPixmap(":/cursor/cur2"), 13, 19)
#define cursorFlipSummon QCursor(QPixmap(":/cursor/cur1"), 13, 19)
#define cursorDefencePosition QCursor(QPixmap(":/cursor/cur6"), 14, 21)
#define cursorAttackPosition QCursor(QPixmap(":/cursor/cur8"), 14, 21)
#define cursorAttack QCursor(QPixmap(":/cursor/cur7"), 14, 19)
#define cursorSelect QCursor(QPixmap(":/cursor/cur3"), 31, 15)

CardItem::CardItem(Card* _card) : card(_card)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    finger = CardItem::No_Finger;
}

void CardItem::setFingerCursor(CardItem::FingerFlag flag)
{
    switch (flag)
    {
    case CardItem::No_Finger:
        setCursor(cursorNoFlag);
        break;
    case CardItem::EffectFromHand_Finger:
        setCursor(cursorEffect);
        break;
    case CardItem::EffectFromFieldyard_Finger:
        setCursor(cursorEffect);
        break;
    case CardItem::EffectFromFieldground_Finger:
        setCursor(cursorEffect);
        break;
    case CardItem::SpecialSummon_Finger:
        setCursor(cursorSpecialSummon);
        break;
    case CardItem::NormalSummon_Finger:
        setCursor(cursorNormalSummon);
        break;
    case CardItem::SetCard_Finger:
        setCursor(cursorSetCard);
        break;
    case CardItem::FlipSummon_Finger:
        setCursor(cursorFlipSummon);
        break;
    case CardItem::DefencePosition_Finger:
        setCursor(cursorDefencePosition);
        break;
    case CardItem::AttackPosition_Finger:
        setCursor(cursorAttackPosition);
        break;
    case CardItem::Attack_Finger:
        setCursor(cursorAttack);
        break;
    case CardItem::Select_Finger:
        setCursor(cursorSelect);
        break;
    }
    update();
}

QString CardItem::getName()
{
    return card->name;
}

QString CardItem::getDescription()
{
    return card->description;
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    emit hoverEnter();

    if (card->area == Card::Hand_Area)
    {
        setY(529-35);
    }
    else if (card->area == Card::EnemyHand_Area)
    {
        setY(-71+35);
    }

    if(!qDota->whoIsDoing) //对方行动
    {
        return;
    }

    if(qDota->isSearchingTargetCard()) //如果正在选择目标
    {
        qDebug() << "isSearchingTargetCard";
        if(qDota->authenticateCard(card)) //hover的是需要的目标
        {
            qDebug() << "authenticateCard";
//          高亮hover的卡牌
            if(qDota->getSearchReason()==Dota::ChainDeclared_Reason)
            {
                qDebug() << "currentTargetReason ChainDeclared_Reason";
                setCursor(cursorEffect);
            }
            if(qDota->getSearchReason()==Dota::BeEquiped_Reason)
            {
                qDebug() << "currentTargetReason BeEquiped_Reason";
                finger = CardItem::Select_Finger;
                setFingerCursor(finger);
            }
        }
        return; //只要是正在选择目标状态，都return
    }

    fingerList.clear();
    if (card->testEffectFromHand())
    {
        fingerList << EffectFromHand_Finger;
    }
    if (card->testSpecialSummon())
    {
        fingerList << SpecialSummon_Finger;
    }
    if (card->testNormalSummon())
    {
        fingerList << NormalSummon_Finger;
    }
    if (card->testSetCard())
    {
        fingerList << SetCard_Finger;
    }
    if(card->testEffectFromFieldyard() > 0)
    {
        fingerList << EffectFromFieldyard_Finger;
    }
    if (card->testDefencePosition())
    {
        fingerList << DefencePosition_Finger;
    }
    if (card->testAttackPosition())
    {
        fingerList << AttackPosition_Finger;
    }
    if (card->testFlipSummon())
    {
        fingerList << FlipSummon_Finger;
    }
    if (card->testEffectFromFieldground())
    {
        fingerList << EffectFromFieldground_Finger;
    }
    if (card->testAttack())
    {
        fingerList << Attack_Finger;
    }

    if(fingerList.isEmpty())
    {
        return;
    }
    finger = fingerList.first();
    setFingerCursor(finger);
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (card->area == Card::Hand_Area)
    {
        setY(529);
    }
    else if(card->area == Card::EnemyHand_Area)
    {
        setY(-71);
    }

    clearFinger();

    if(!qDota->whoIsDoing)
    {
        return;
    }
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    if(!qDota->whoIsDoing)
    {
        return;
    }

    if(qDota->isSearchingTargetCard()) //如果正在选择目标
    {
        qDebug() << "isSearchingTargetCard";
        if(event->button() != Qt::LeftButton)
        {
            return;
        }
        if(qDota->authenticateCard(card)) //press 的是需要的目标
        {
            qDebug() << "authenticateCard";
            Dota::ReasonFlag flag = qDota->getSearchReason();
            qDota->chainStack << flag;
            qDota->setSearchReason(Dota::No_Reason); //清除所有鉴权条件

            if(flag == Dota::BeAttacked_Reason)
            {
                qDebug() << "currentTargetReason == Dota::BeAttacked_Reason";
                qDota->attackDestinationCard = card;
                emit beAttacked();
            }
            else if(flag == Dota::ChainDeclared_Reason)
            {
                qDebug() << "currentTargetReason == Dota::ChainDeclared_Reason";
                qDota->chainCard = card;
                clearFinger();
                emit chainDeclared();
            }
            else if(flag == Dota::BeEquiped_Reason)
            {
                qDebug() << "currentTargetReason";
                emit beEquiped();
            }
        }
        else
        {
            //卡牌上面提示：此卡无法作为对象选择。<---- 指我攻击对象不能是自己怪兽
            //This card cannot be targeted.
        }
        return; //只要是选择目标状态，都return
    }

    if(event->button() == Qt::LeftButton)
    {
        if(fingerList.isEmpty())
        {
            return;
        }
        switch (finger)
        {
        case CardItem::No_Finger:
            return;
        case CardItem::EffectFromHand_Finger://暂时没过滤怪兽卡,发动魔法卡
            active();
            break;
        case CardItem::EffectFromFieldyard_Finger:
            //card->effectFromFieldyard();
            break;
        case CardItem::EffectFromFieldground_Finger:
            break;
        case CardItem::SpecialSummon_Finger:
            specialSummon();
            break;
        case CardItem::NormalSummon_Finger:
            summon();
            break;
        case CardItem::SetCard_Finger:
            set();
            break;
        case CardItem::FlipSummon_Finger:
//            card->flipSummon();
            break;
        case CardItem::DefencePosition_Finger:
//            card->defencePosition();
            break;
        case CardItem::AttackPosition_Finger:
//            card->attackPosition();
            break;
        case CardItem::Attack_Finger:
            attack();
            break;
        default:
            break;
        }

        clearFinger();
    }
    else if(event->button() == Qt::RightButton)
    {
        if(fingerList.isEmpty() || finger==CardItem::No_Finger)
        {
            return;
        }
        int index = fingerList.indexOf(finger);
        finger = finger == fingerList.last() ? fingerList.first() : fingerList.at(index + 1);
        setFingerCursor(finger);
    }
}

void CardItem::clearFinger()
{
    fingerList.clear();
    finger = FingerFlag::No_Finger;
    setFingerCursor(finger);
}

void CardItem::setup()
{
    card->setupCard();
    emit moveCardItem(Card::No_Area,Card::Deck_Area);
}

void CardItem::enemySetup()
{
    card->enemySetupCard();
    emit moveCardItem(Card::No_Area,Card::EnemyDeck_Area);
}

void CardItem::draw()
{
    card->drawCard();
    emit moveCardItem(Card::Deck_Area,Card::Hand_Area);
    qNet->sendDraw();
}

void CardItem::response_drawFirst()
{
    card->enemyDrawCard();
    emit moveCardItem(Card::EnemyDeck_Area,Card::EnemyHand_Area);
}

void CardItem::specialSummon()
{
    int index = qDota->handCards.indexOf(card);
    //先card.area 再item.pos 最后qDota.list,省去了很多emit
    card->specialSummonCard();
    emit moveCardItem(Card::Hand_Area,Card::Fieldyard_Area);
    qNet->sendSpecialSummon(index);
}

void CardItem::response_specialSummon()
{
    card->enemySpecialSummonCard();
    emit moveCardItem(Card::EnemyHand_Area,Card::EnemyFieldyard_Area);
}

void CardItem::active()
{
    int index = qDota->handCards.indexOf(card);
    card->activeCard();
    emit moveCardItem(Card::Hand_Area,Card::Fieldground_Area);
    qNet->sendActive(index);

    card->active();
}

void CardItem::response_active()
{
    card->enemyActiveCard();
    emit moveCardItem(Card::EnemyHand_Area,Card::EnemyFieldground_Area);
}

void CardItem::summon()
{
    int index = qDota->handCards.indexOf(card);
    card->summonCard();
    emit moveCardItem(Card::Hand_Area,Card::Fieldyard_Area);
    qNet->sendSummon(index);
}

void CardItem::response_summon()
{
    card->enemySummonCard();
    emit moveCardItem(Card::EnemyHand_Area,Card::EnemyFieldyard_Area);
}

void CardItem::set()
{
    int index = qDota->handCards.indexOf(card);
    card->setCard();
    emit moveCardItem(Card::Hand_Area,Card::Fieldyard_Area);
    qNet->sendSet(index);
}

void CardItem::response_set()
{
    card->enemySetCard();
    emit moveCardItem(Card::EnemyHand_Area,Card::EnemyFieldyard_Area);
}

void CardItem::attack()
{
    qDota->attackSourceCard = card;
    if(qDota->hasEnemyMonster())
    {
        qDota->setSearchReason(Dota::BeAttacked_Reason);
    }
    else
    {
        emit beAttacked();
    }
}

void CardItem::battleSource()
{
    int index = qDota->getCardIndexOfFieldyard(card);
    Card* targetCard = qDota->attackDestinationCard;
    if(targetCard->stand) //被攻击者攻击表示
    {
        if(card->ATK <= targetCard->ATK)
        {
            card->destroyCard();
            emit moveCardItem(Card::Fieldyard_Area,Card::Graveyard_Area);
            qNet->sendDestroyFieldyard(index);
        }
    }
}

void CardItem::battleTarget()
{
    int index = qDota->getCardIndexOfEnemyFieldyard(card);
    Card* sourceCard = qDota->attackSourceCard;
    if(sourceCard->stand) //被攻击者攻击表示
    {
        if(card->ATK <= sourceCard->ATK)
        {
            card->enemyDestroyCard();
            emit moveCardItem(Card::EnemyFieldyard_Area,Card::EnemyGraveyard_Area);
            qNet->sendDestroyEnemyFieldyard(index);
        }
    }
}

void CardItem::response_enemyDestroyFieldyard()
{
    card->enemyDestroyCard();
    emit moveCardItem(Card::EnemyFieldyard_Area,Card::EnemyGraveyard_Area);
}

void CardItem::response_destroyFieldyard()
{
    card->destroyCard();
    emit moveCardItem(Card::Fieldyard_Area,Card::Graveyard_Area);
}

void CardItem::changeImage()
{
    QString prefix, framePrefix;
    qreal x=0, y=0, angle;

    if(card->area == Card::Deck_Area
       || card->area == Card::Fieldyard_Area
       || card->area == Card::Fieldground_Area
       || card->area == Card::Graveyard_Area
       || card->area == Card::EnemyDeck_Area
       || card->area == Card::EnemyFieldyard_Area
       || card->area == Card::EnemyFieldground_Area
       || card->area == Card::EnemyGraveyard_Area)
    {
        prefix = "field";
        x = 25;
        y = 36;
        framePrefix = "select";
    }
    else if(card->area == Card::Hand_Area
            || card->area == Card::EnemyHand_Area)
    {
        prefix = "hand";
        x = 50;
        y = 72;
        framePrefix = "choose";
    }

    if(card->enemy)
    {
        angle = 180;
        frameImage = QImage(QString(":/png/%1Red").arg(framePrefix));
    }
    else
    {
        angle = 0;
        frameImage = QImage(QString(":/png/%1Blue").arg(framePrefix));
    }
//    if(card->face)
//    {
        setPixmap(QPixmap(QString(":/%1/%2").arg(prefix).arg(card->name)));
//    }
//    else
//    {
//        setPixmap(QPixmap(QString(":/%1/NULL").arg(prefix)));
//    }

    setTransformOriginPoint(x, y);
    if(card->stand)
    {
        setRotation(angle);
    }
    else
    {
        setRotation(-90-angle);
    }

    originalPixmap = pixmap();
    QImage image = pixmap().toImage();
    for(int i=0;i<image.width();i++)
    {
        for(int j=0;j<image.height();j++)
        {
            image.setPixelColor(i,j,image.pixelColor(i,j).lighter(165));
        }
    }
    lighterPixmap = QPixmap::fromImage(image);
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(card->area==Card::No_Area)
    {
        return;
    }

    if(finger!=No_Finger)
    {
        painter->drawPixmap(0, 0, lighterPixmap);
    }
    else
    {
        painter->drawPixmap(0, 0, originalPixmap);
    }

    //frame框有bug 先不显示了
//    if(isUnderMouse() && card->area!=Card::Hand_Area && card->area!=Card::EnemyHand_Area) //往右移动hover，左边卡牌边框不消失
//    {
//        painter->drawPixmap(-3,-3,QPixmap::fromImage(frameImage));
//    }
}
