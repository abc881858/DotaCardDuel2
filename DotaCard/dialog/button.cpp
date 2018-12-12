#include "button.h"

Button::Button(const QString &filename, bool center_as_origin)
    : pixmap(filename)
{
    if(center_as_origin)
    {
        setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
    }
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    emit hoverEnter();
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    emit hoverLeave();
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

QRectF Button::boundingRect() const
{
    return QRectF{0, 0, qreal(pixmap.width()), qreal(pixmap.height())};
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void Button::setPixmap(const QString& filename)
{
    pixmap.load(filename);
}
