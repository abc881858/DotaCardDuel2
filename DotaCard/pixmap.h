#ifndef PIXMAP_H
#define PIXMAP_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

class Pixmap : public QGraphicsObject
{
    Q_OBJECT
public:
    Pixmap(const QString &filename, bool center_as_origin = true);
    Pixmap(QPixmap q);
    QPixmap pixmap;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;
    void timerEvent(QTimerEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
public:
    void setPixmap(QString filename);
    void doShineAnimation();
    void changePhaseAnimation();
    void effect();
    void actionAnimation();
    void swordAnimation(QPointF p1, QPointF p2);

    void doEquipAnimation(QPointF positionFrom, QPointF positionTo);
    void doEquipHoverAnimation();
    void doneEquipHoverAnimation();
private:
    QPropertyAnimation *hide_pix;
    QPropertyAnimation *action_start;
    QPropertyAnimation* animation;
    QPropertyAnimation *fadeEquip;

    int z;
    int id;

signals:
    void finishedDoShineAnimation();
    void finishedActionAnimation();
    void finishedSwordAnimation();
    void finishedEquipAnimation();

    void hoverEnter();
    void hoverLeave();
    void clicked();
};

#endif // PIXMAP_H
