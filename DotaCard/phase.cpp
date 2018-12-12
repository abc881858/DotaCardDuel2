#include "phase.h"
#include <QPainter>
#include <QTimerEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Phase::Phase(const QString& name) : pixmap(QString("phase/%1.bmp").arg(name)),
    targetRect(0,0,40,75), sourceRect(0,0,40,75), name(name), turn("blue"), x(0)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    id = 0;

    connect(this,SIGNAL(finish()),this,SLOT(blue_red()));
}

QRectF Phase::boundingRect() const
{
    return {0, 0, 40, 75};
}

void Phase::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(targetRect, pixmap, sourceRect);
}

void Phase::timerEvent(QTimerEvent *)
{
    sourceRect.setRect(x,0,40,75);
    update();
    x=x+40;
    if(x==360)
    {
        emit finish();
    }
}

void Phase::effect()
{
    pixmap=QPixmap(QString("phase/%1_%2.bmp").arg(name, turn));
    id = startTimer(10);
}

void Phase::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    pixmap=QPixmap(QString("phase/%1.bmp").arg(name));
    if(turn=="blue")
    {
        sourceRect.setRect(40,0,40,75);
    }
    else
    {
        sourceRect.setRect(40,75,40,75);
    }
    update();
    emit hover();
}

void Phase::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    pixmap=QPixmap(QString("phase/%1.bmp").arg(name));
    if(turn=="blue")
    {
        sourceRect.setRect(0,0,40,75);
    }
    else
    {
        sourceRect.setRect(0,75,40,75);
    }
    update();
}

void Phase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        emit clicked();
    }
}

void Phase::blue_red()
{
    killTimer(id);
    id = 0;
    x=0;

    if(turn=="blue")
    {
        turn="red";
    }
    else
    {
        turn="blue";
    }

    pixmap=QPixmap(QString("phase/%1.bmp").arg(name));

    if(turn=="red")
    {
        sourceRect.setRect(0,75,40,75);
    }
    else
    {
        sourceRect.setRect(0,0,40,75);
    }
    update();
}
