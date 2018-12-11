#include "selectdialog.h"
#include <QDebug>
#include "dota.h"
#include "button.h"

SelectDialog::SelectDialog(const QString &filename)
    : pixmap(filename)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    scrollArea = new QScrollArea;
    widget = new QWidget;
    layout = new QHBoxLayout;
    layout->setContentsMargins(15,0,15,0);
    layout->setSpacing(22);
    widget->setLayout(layout);

    scrollArea->setWidget(widget);
    scrollArea->setStyleSheet("QScrollArea {background-color:transparent;}");
    scrollArea->viewport()->setStyleSheet("background-color:transparent;");
    widget->setStyleSheet("background-color:transparent;");
    scrollArea->setFixedSize(370, 100);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    proxy = new QGraphicsProxyWidget;
    proxy->setWidget(scrollArea);
    proxy->setParentItem(this);
    proxy->setPos(40,49);
    proxy->setZValue(10);
}

QRectF SelectDialog::boundingRect() const
{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void SelectDialog::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void SelectDialog::showAnimation()
{
    qDebug() << "showAnimation";
    QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
    action->setStartValue(QPointF(292,-160));
    action->setEndValue(QPointF(292,226));
    action->setDuration(600);
    action->setEasingCurve(QEasingCurve::OutSine);
    action->start(QAbstractAnimation::DeleteWhenStopped);
}

void SelectDialog::buildDialog()
{
    if(area == 1) //从卡组
    {
        for(Card* card : qDota->deckCards)
        {
            j++;
            if(card->getLevel() <= level)
            {
                i++;
                QPushButton *button = new QPushButton;
                button->setFixedSize(50,72);
                button->setStyleSheet(QString("border-image: url(%1);").arg(card->getFieldPath()));
                layout->addWidget(button);

                connect(button, &QPushButton::clicked, this, &SelectDialog::hideAnimation);
            }
        }
        widget->setFixedSize(72*i+30, 80);
        update();
    }
}

void SelectDialog::hideAnimation()
{
    QPropertyAnimation *action = new QPropertyAnimation(this,"pos");
    action->setStartValue(QPointF(292,226));
    action->setEndValue(QPointF(292,-160));
    action->setDuration(600);
    action->setEasingCurve(QEasingCurve::InQuad);
    action->start(QAbstractAnimation::DeleteWhenStopped);
    connect(action,&QPropertyAnimation::finished, [=](){
        emit selected(i);
        i = -1;
        j = -1;
    });
}
