#include "centaurwarrunnerdialog.h"
#include <QDebug>
#include "dota.h"

CentaurWarrunnerDialog::CentaurWarrunnerDialog(const QString &filename)
    : pixmap(filename)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    button1 = new Button(":/png/centaurwarrunner0");
    button1->setAcceptHoverEvents(true);
    button1->setPos(64,81);
    button1->setParentItem(this);
    button1->setZValue(8);
    button1->show();

    connect(button1,&Button::hoverEnter, [=](){
        button1->setPixmap(":/png/centaurwarrunner1");
        button1->update();
    });
    connect(button1,&Button::hoverLeave, [=](){
        button1->setPixmap(":/png/centaurwarrunner0");
        button1->update();
    });

    button2 = new Button(":/png/centaurwarrunner0");
    button2->setAcceptHoverEvents(true);
    button2->setPos(66,125);
    button2->setParentItem(this);
    button2->setZValue(8);
    button2->show();

    connect(button2,&Button::hoverEnter, [=](){
        button2->setPixmap(":/png/centaurwarrunner2");
        button2->update();
    });
    connect(button2,&Button::hoverLeave, [=](){
        button2->setPixmap(":/png/centaurwarrunner0");
        button2->update();
    });

    button3 = new Button(":/png/centaurwarrunner0");
    button3->setAcceptHoverEvents(true);
    button3->setPos(66,171);
    button3->setParentItem(this);
    button3->setZValue(8);
    button3->show();

    connect(button3,&Button::hoverEnter, [=](){
        button3->setPixmap(":/png/centaurwarrunner3");
        button3->update();
    });
    connect(button3,&Button::hoverLeave, [=](){
        button3->setPixmap(":/png/centaurwarrunner0");
        button3->update();
    });

    connect(button1,&Button::clicked,[=](){
        QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
        action->setStartValue(QPointF(292,226));
        action->setEndValue(QPointF(292,-160));
        action->setDuration(600);
        action->setEasingCurve(QEasingCurve::InQuad);
        action->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action,&QPropertyAnimation::finished, [=](){
            button1->setPixmap(":/png/centaurwarrunner0");
            button1->update();
            emit clicked_button(1);
        });
    });

    connect(button2,&Button::clicked,[=](){
        QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
        action->setStartValue(QPointF(292,226));
        action->setEndValue(QPointF(292,-160));
        action->setDuration(600);
        action->setEasingCurve(QEasingCurve::InQuad);
        action->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action,&QPropertyAnimation::finished, [=](){
            button2->setPixmap(":/png/centaurwarrunner0");
            button2->update();
            emit clicked_button(2);
        });
    });

    connect(button3,&Button::clicked,[=](){
        QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
        action->setStartValue(QPointF(292,226));
        action->setEndValue(QPointF(292,-160));
        action->setDuration(600);
        action->setEasingCurve(QEasingCurve::InQuad);
        action->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action,&QPropertyAnimation::finished, [=](){
            button3->setPixmap(":/png/centaurwarrunner0");
            button3->update();
            emit clicked_button(3);
        });
    });
}

QRectF CentaurWarrunnerDialog::boundingRect() const
{
    return {0, 0, qreal(pixmap.width()), qreal(pixmap.height())};
}

void CentaurWarrunnerDialog::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void CentaurWarrunnerDialog::showAnimation()
{
    QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
    action->setStartValue(QPointF(292,-160));
    action->setEndValue(QPointF(292,226));
    action->setDuration(600);
    action->setEasingCurve(QEasingCurve::OutSine);
    action->start(QAbstractAnimation::DeleteWhenStopped);
}
