#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>

class Button : public QGraphicsObject
{
    Q_OBJECT
public:
    Button(const QString &filename, bool center_as_origin = true);
    QPixmap pixmap;
    void setPixmap(QString filename);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void hoverEnter();
    void hoverLeave();
    void clicked();
};

#endif // BUTTON_H
