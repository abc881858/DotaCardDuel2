#include "carditem.h"
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QImage>
#include <QPainter>
#include "room.h"

CardItem::CardItem(Card* card)
    : Spirit(":/area/NULL"),
      m_card(card)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

CardItem::PlaceFlag CardItem::getPlace() const
{
    return m_place;
}

void CardItem::setPlace(CardItem::PlaceFlag place)
{
    m_place = place;

    switch (m_place)
    {
    case Deck_Place:
        m_card->setArea(Card::Deck_Area);
        break;
    case Hand_Place:
        m_card->setArea(Card::Hand_Area);
        break;
    case Front_Place:
        m_card->setArea(Card::Front_Area);
        break;
    case Back_Place:
        m_card->setArea(Card::Back_Area);
        break;
    case Grave_Place:
        m_card->setArea(Card::Grave_Area);
        break;
    case Remote_Deck_Place:
        m_card->setArea(Card::Remote_Deck_Area);
        break;
    case Remote_Hand_Place:
        m_card->setArea(Card::Remote_Hand_Area);
        break;
    case Remote_Front_Place:
        m_card->setArea(Card::Remote_Front_Area);
        break;
    case Remote_Back_Place:
        m_card->setArea(Card::Remote_Back_Area);
        break;
    case Remote_Grave_Place:
        m_card->setArea(Card::Remote_Grave_Area);
        break;
    default:
        m_card->setArea(Card::No_Area);
        break;
    }
}

void CardItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    qRoom->update_big_image(getFileNameLarge());
    update_big_image(getFileNameLarge());

    if (m_place == CardItem::Hand_Place)
    {
        setY(529-35);
    }
    else if (m_place == CardItem::Remote_Hand_Place)
    {
        setY(-71+35);
    }

    if(m_card->testActive())
    {
        setCursor(QCursor(QPixmap(":/cursor/4")));
    }

//    if(m_card->getArea() == Card::Fieldyard_Area)
//    {
//        qDota->beHoverFieldyard(card);
//    }

//    if(m_card->getArea() == Card::Fieldground_Area)
//    {
//        qDota->beHoverFieldground(card);
//    }

//    if(!qDota->whoIsDoing) //对方行动
//    {
//        return;
//    }

//    if(qDota->isSearchingTargetCard()) //如果正在选择目标
//    {
//        qDebug() << "isSearchingTargetCard";
//        if(qDota->authenticateCard(card)) //hover的是需要的目标
//        {
//            qDebug() << "authenticateCard";
////          高亮hover的卡牌
////            if(qDota->getSearchReason()==Dota::ChainDeclared_Reason)
////            {
////                qDebug() << "currentTargetReason ChainDeclared_Reason";
////                setCursor(cursorEffect);
////            }
//            if(qDota->getSearchReason()==Dota::BeEquiped_Reason)
//            {
//                qDebug() << "currentTargetReason BeEquiped_Reason";
//                finger = CardItem::Select_Finger;
//                setFingerCursor(finger);
//            }
//        }
//        return; //只要是正在选择目标状态，都return
//    }
}

void CardItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit hoverLeave();

    if (m_place == CardItem::Hand_Place)
    {
        setY(529);
    }
    else if(m_place == CardItem::Remote_Hand_Place)
    {
        setY(-71);
    }

//    if(m_card->getArea() == Card::Fieldyard_Area)
//    {
//        qDota->beLeaveFieldyard(card);
//    }

//    if(m_card->getArea() == Card::Fieldground_Area)
//    {
//        qDota->beLeaveFieldground(card);
//    }

//    clearFinger();

//    if(!qDota->whoIsDoing)
//    {
//        return;
//    }
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
////    emit mousePress();

//    if(qDota->isSearchingTargetCard()) //如果正在选择目标
//    {
//        qDebug() << "isSearchingTargetCard";
//        if(event->button() != Qt::LeftButton)
//        {
//            return;
//        }
//        if(qDota->authenticateCard(card)) //press 的是需要的目标
//        {
//            qDebug() << "authenticateCard";
//            Dota::ReasonFlag flag = qDota->getSearchReason();
//            qDota->chainStack << flag;
//            qDota->setSearchReason(Dota::No_Reason); //清除所有鉴权条件

//            if(flag == Dota::BeAttacked_Reason)
//            {
//                qDebug() << "currentTargetReason == Dota::BeAttacked_Reason";
//                qDota->attackDestinationCard = card;
//                qDota->attackSourceCard->canAttack = false;
//                qDota->beAttacked();
//            }
////            else if(flag == Dota::ChainDeclared_Reason)
////            {
////                qDebug() << "currentTargetReason == Dota::ChainDeclared_Reason";
////                qDota->chainCard = card;
////                clearFinger();
////                qDota->chainDeclared();
////            }
//            else if(flag == Dota::BeEquiped_Reason)
//            {
//                qDebug() << "currentTargetReason == Dota::BeEquiped_Reason";
//                qDota->equipMonsterCard = card;
//                qDota->beEquiped();
//            }
//        }
//        else
//        {
//            //卡牌上面提示：此卡无法作为对象选择。<---- 指我攻击对象不能是自己怪兽
//            //This card cannot be targeted.
//        }
//        return; //只要是选择目标状态，都return
//    }

//    if(event->button() == Qt::LeftButton)
//    {
//        if(fingerList.isEmpty())
//        {
//            return;
//        }
//        switch (finger)
//        {
//        case CardItem::No_Finger:
//            return;
//        case CardItem::EffectFromHand_Finger://暂时没过滤怪兽卡,发动魔法卡
//            if(card->getKind() == Card::EquipSpell_Kind)
//            {
//                card->beforeEquip();
//            }
//            break;
//        case CardItem::EffectFromFieldyard_Finger:
//            card->active();
//            break;
//        case CardItem::EffectFromFieldground_Finger:
//            card->active();
//            break;
//        case CardItem::SpecialSummon_Finger:
//            card->specialSummonCard();
//            break;
//        case CardItem::NormalSummon_Finger:
//            card->summonCard();
//            break;
//        case CardItem::SetCard_Finger:
//            card->setCard();
//            break;
//        case CardItem::FlipSummon_Finger:
////            card->flipSummon();
//            break;
//        case CardItem::DefencePosition_Finger:
////            card->defencePosition();
//            break;
//        case CardItem::AttackPosition_Finger:
////            card->attackPosition();
//            break;
//        case CardItem::Attack_Finger:
//            qDota->attack(card);
//            break;
//        default:
//            break;
//        }

//        clearFinger();
//    }
//    else if(event->button() == Qt::RightButton)
//    {
//        if(fingerList.isEmpty() || finger==CardItem::No_Finger)
//        {
//            return;
//        }
//        int index = fingerList.indexOf(finger);
//        finger = finger == fingerList.last() ? fingerList.first() : fingerList.at(index + 1);
//        setFingerCursor(finger);
//    }
}

void CardItem::changeImage()
{
    QString prefix; //, framePrefix;
    qreal x=0, y=0, angle;

    if( m_place == CardItem::Deck_Place ||
        m_place == CardItem::Front_Place ||
        m_place == CardItem::Back_Place ||
        m_place == CardItem::Grave_Place ||
        m_place == CardItem::Remote_Deck_Place ||
        m_place == CardItem::Remote_Front_Place ||
        m_place == CardItem::Remote_Back_Place ||
        m_place == CardItem::Remote_Grave_Place )
    {
        prefix = "area";
        x = 25;
        y = 36;
//        framePrefix = "select";
    }
    else if( m_place == CardItem::Hand_Place ||
             m_place == CardItem::Remote_Hand_Place )
    {
        prefix = "hand";
        x = 50;
        y = 72;
//        framePrefix = "choose";
    }

    if( m_place == CardItem::Remote_Deck_Place ||
        m_place == CardItem::Remote_Hand_Place ||
        m_place == CardItem::Remote_Front_Place ||
        m_place == CardItem::Remote_Back_Place ||
        m_place == CardItem::Remote_Grave_Place )
    {
        angle = 180;
    }
    else
    {
        angle = 0;
    }

//    if(card->enemy)
//    {
//        angle = 180;
//        frameImage = QImage(QString(":/png/%1Red").arg(framePrefix));
//    }
//    else
//    {
//        angle = 0;
//        frameImage = QImage(QString(":/png/%1Blue").arg(framePrefix));
//    }
//    if(card->face)
//    {
        setPixmap(QString(":/%1/%2").arg(prefix, m_card->getName()));
//    }
//    else
//    {
//        setPixmap(QPixmap(QString(":/%1/NULL").arg(prefix)));
//    }

    setTransformOriginPoint(x, y);
    if(m_card->getStand())
    {
        setRotation(angle);
    }
    else
    {
        setRotation(-90-angle);
    }

    originalPixmap = getPixmap();
    QImage image = getPixmap().toImage();
    for(int i=0;i<image.width();i++)
    {
        for(int j=0;j<image.height();j++)
        {
            image.setPixelColor(i,j,image.pixelColor(i,j).lighter(165));
        }
    }
    lighterPixmap = QPixmap::fromImage(image);
}

QString CardItem::getFileNameLarge()
{
    return QString(":/info/").append(m_card->getName());
}

QString CardItem::getFileNameMedium()
{
    return QString(":/hand/").append(m_card->getName());
}

QString CardItem::getFileNameSmall()
{
    return QString(":/area/").append(m_card->getName());
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(m_place==CardItem::No_Place)
    {
        return;
    }

//    if(finger!=No_Finger)
//    {
//        painter->drawPixmap(0, 0, lighterPixmap);
//    }
//    else
//    {
//        painter->drawPixmap(0, 0, originalPixmap);
//    }

    painter->drawPixmap(0, 0, originalPixmap);

    //frame框有bug 先不显示了
//    if(isUnderMouse() && card->area!=Card::Hand_Area && card->area!=Card::EnemyHand_Area) //往右移动hover，左边卡牌边框不消失
//    {
//        painter->drawPixmap(-3,-3,QPixmap::fromImage(frameImage));
//    }
}
