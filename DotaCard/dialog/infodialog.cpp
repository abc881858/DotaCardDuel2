#include "infodialog.h"
#include <QDebug>
#include "dota.h"

InfoDialog::InfoDialog(const QString &filename)
    : pixmap(filename)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    button = new Pixmap(":/png/disable");
    button->setAcceptHoverEvents(true);
    button->setPos(151,75);
    button->setParentItem(this);
    button->setZValue(8);
    button->show();

    connect(button,&Pixmap::hoverEnter, [=](){
        button->setPixmap(":/png/enable");
        button->update();
    });
    connect(button,&Pixmap::hoverLeave, [=](){
        button->setPixmap(":/png/disable");
        button->update();
    });

    connect(button,&Pixmap::clicked,[=](){
        QPropertyAnimation *action2 = new QPropertyAnimation(this,"pos");
        action2->setStartValue(QPointF(292,226));
        action2->setEndValue(QPointF(292,-160));
        action2->setDuration(600);
        action2->setEasingCurve(QEasingCurve::InQuad);
        action2->start(QAbstractAnimation::DeleteWhenStopped);
        connect(action2,&QPropertyAnimation::finished, [=](){
            this->hide();
            this->deleteLater();
            qDota->whoIsDoing = true;
            qDota->setSearchReason(Dota::BeEquiped_Reason);
        });
    });
}

QRectF InfoDialog::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void InfoDialog::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void InfoDialog::showAnimation()
{
    qDebug() << "showAnimation";
    QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
    action->setEndValue(QPointF(292,226));
    action->setDuration(600);
    action->setEasingCurve(QEasingCurve::InQuad);
    action->start(QAbstractAnimation::DeleteWhenStopped);
}
