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
    if(card->testEffectFromFieldyard())
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
    emit hoverLeave();

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
//    emit mousePress();


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
                qDota->attackSourceCard->canAttack = false;
                qDota->beAttacked();
            }
            else if(flag == Dota::ChainDeclared_Reason)
            {
                qDebug() << "currentTargetReason == Dota::ChainDeclared_Reason";
                qDota->chainCard = card;
                clearFinger();
                qDota->chainDeclared();
            }
            else if(flag == Dota::BeEquiped_Reason)
            {
                qDebug() << "currentTargetReason == Dota::BeEquiped_Reason";
                qDota->equipMonsterCard = card;
                qDota->beEquiped();
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
            qDota->activeSpellCard(card);//active();
            break;
        case CardItem::EffectFromFieldyard_Finger:
            card->active();
            break;
        case CardItem::EffectFromFieldground_Finger:
            card->active();
            break;
        case CardItem::SpecialSummon_Finger:
            qDota->specialSummonCard(card);
            break;
        case CardItem::NormalSummon_Finger:
            qDota->summonCard(card);
            break;
        case CardItem::SetCard_Finger:
            qDota->setCard(card);
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
            qDota->attack(card);
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
        setPixmap(QPixmap(QString(":/%1/%2").arg(prefix, card->name)));
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
