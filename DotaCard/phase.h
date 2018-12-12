#ifndef PHASE_H
#define PHASE_H

#include <QGraphicsObject>

class Phase : public QGraphicsObject
{
    Q_OBJECT
public:
    Phase(const QString& name);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
protected:
    void timerEvent(QTimerEvent *);
private:
    QPixmap pixmap;
    QRectF targetRect;
    QRectF sourceRect;
    QString name;
    QString turn;
    int x;
    int id;
signals:
    void finish();
    void hover();
    void clicked();
public slots:
    void blue_red();
public:
    void effect();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PHASE_H
