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
    QPixmap pixmap;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;
    void timerEvent(QTimerEvent*);

public:
    void setPixmap(QString filename);
    void doShineAnimation();
    void changePhaseAnimation();
    void effect();
    void actionAnimation();
    void swordAnimation(QPointF p1, QPointF p2);

private:
    QPropertyAnimation *hide_pix;
    QPropertyAnimation *action_start;
    QPropertyAnimation* animation;

    int z;
    int id;

signals:
    void finishedEffect();
    void finishedDoShineAnimation();
    void finishedChangePhaseAnimation();
    void finishedActionAnimation();
    void finishedSwordAnimation();

};

#endif // PIXMAP_H
