#include "button.h"
#include <QDebug>
#include <QGraphicsScene>

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    qDebug() << scene()->metaObject()->className() << "Button::hoverEnterEvent";
    emit hoverEnter();
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    qDebug() << scene()->metaObject()->className() << "Button::hoverLeaveEvent";
    emit hoverLeave();
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << scene()->metaObject()->className() << "Button::mousePressEvent";
    emit clicked();
}
