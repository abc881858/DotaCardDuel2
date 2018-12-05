#ifndef CARDITEM_H
#define CARDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "card.h"

class CardItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum FingerFlag
    {
        No_Finger,
        EffectFromHand_Finger,
        SpecialSummon_Finger,
        NormalSummon_Finger,
        SetCard_Finger,
        EffectFromFieldyard_Finger,
        DefencePosition_Finger, //可以防守表示
        AttackPosition_Finger, //可以攻击表示
        FlipSummon_Finger, //可以翻转召唤
        EffectFromFieldground_Finger,
        Attack_Finger,
        Select_Finger //可以选择（作为装备魔法卡目标）
    };
    explicit CardItem(Card *_card);
    void setFingerCursor(CardItem::FingerFlag flag);

    QString getName();
    QString getDescription();

    void changeImage();
    void clearFinger();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget);

private:
    QList<FingerFlag> fingerList;
    FingerFlag finger;

    Card *card;

    QPixmap lighterPixmap;
    QPixmap originalPixmap;
    QImage frameImage;

signals:
    void hoverEnter();
    void hoverLeave();
    void mousePress();

};

#endif // CARDITEM_H
