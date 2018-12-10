#include "warningdialog.h"
#include <QDebug>
#include "dota.h"

WarningDialog::WarningDialog(const QString &filename)
    : pixmap(filename)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    buttonYes = new Button(":/png/disable");
    buttonYes->setAcceptHoverEvents(true);
    buttonYes->setPos(82,74);
    buttonYes->setParentItem(this);
    buttonYes->setZValue(8);
    buttonYes->show();

    connect(buttonYes,&Button::hoverEnter, [=](){
        buttonYes->setPixmap(":/png/enable_yes");
        buttonYes->update();
    });
    connect(buttonYes,&Button::hoverLeave, [=](){
        buttonYes->setPixmap(":/png/disable");
        buttonYes->update();
    });

    buttonNo = new Button(":/png/disable");
    buttonNo->setAcceptHoverEvents(true);
    buttonNo->setPos(212,73);
    buttonNo->setParentItem(this);
    buttonNo->setZValue(8);
    buttonNo->show();

    connect(buttonNo,&Button::hoverEnter, [=](){
        buttonNo->setPixmap(":/png/enable_no");
        buttonNo->update();
    });
    connect(buttonNo,&Button::hoverLeave, [=](){
        buttonNo->setPixmap(":/png/disable");
        buttonNo->update();
    });

    connect(buttonYes,&Button::clicked,[=](){
        QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
        action->setStartValue(QPointF(292,226));
        action->setEndValue(QPointF(292,-160));
        action->setDuration(600);
        action->setEasingCurve(QEasingCurve::InQuad);
        action->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action,&QPropertyAnimation::finished, [=](){
            buttonYes->setPixmap(":/png/disable");
            buttonYes->update();
            emit clicked_yes();
        });
    });

    connect(buttonNo,&Button::clicked,[=](){
        QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
        action->setStartValue(QPointF(292,226));
        action->setEndValue(QPointF(292,-160));
        action->setDuration(600);
        action->setEasingCurve(QEasingCurve::InQuad);
        action->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action,&QPropertyAnimation::finished, [=](){
            buttonNo->setPixmap(":/png/disable");
            buttonNo->update();
            emit clicked_no();
        });
    });
}

QRectF WarningDialog::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void WarningDialog::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void WarningDialog::showAnimation()
{
    qDebug() << "showAnimation";
    QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
    action->setStartValue(QPointF(292,-160));
    action->setEndValue(QPointF(292,226));
    action->setDuration(600);
    action->setEasingCurve(QEasingCurve::OutSine);
    action->start(QAbstractAnimation::DeleteWhenStopped);
}
