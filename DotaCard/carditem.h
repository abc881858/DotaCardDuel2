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
        Attack_Finger
    };
    explicit CardItem(Card *_card);
    void setFingerCursor(CardItem::FingerFlag flag);

    QString getName();
    QString getDescription();

    void setup();
    void enemySetup();
    void draw();
    void response_drawFirst();
    void specialSummon();
    void response_specialSummon();
    void summon();
    void response_summon();
    void set();
    void response_set();
    void active();
    void response_active();

    void battleSource();
    void battleTarget();
    void response_destroyFieldyard();
    void response_enemyDestroyFieldyard();

    void changeImage();

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
    void moveCardItem(Card::AreaFlag, Card::AreaFlag);
    void hoverEnter();
    void beAttacked();
    void chainDeclared();
    void beEquiped();
};

#endif // CARDITEM_H
