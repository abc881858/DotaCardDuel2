#include "selectdialog.h"
#include <QDebug>
#include "dota.h"

SelectDialog::SelectDialog(const QString &filename)
    : pixmap(filename)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

//    connect(button,&Button::clicked,[=](){
//        QPropertyAnimation *action2 = new QPropertyAnimation(this,"pos");
//        action2->setStartValue(QPointF(292,226));
//        action2->setEndValue(QPointF(292,-160));
//        action2->setDuration(600);
//        action2->setEasingCurve(QEasingCurve::InQuad);
//        action2->start(QAbstractAnimation::DeleteWhenStopped);
//        connect(action2,&QPropertyAnimation::finished, [=](){
//            button->setPixmap(":/png/disable");
//            button->update();
//            emit clicked_pixmap(0,0);
//        });
//    });
    scrollArea = new QScrollArea;
    scrollArea->setFixedSize(370, 80);
    proxy = new QGraphicsProxyWidget;
    proxy->setWidget(scrollArea);
    proxy->setParentItem(this);
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
//    if(area==1) //从卡组
//    {
//        int i = 0;
//        for(Card* card : qDota->deckCards)
//        {
//            if(card->getLevel()<=3)
//            {
//                Button *button = new Button(card->getFieldPath());
//                button->setAcceptHoverEvents(true);
//                button->setPos(51+80*i,55);
//                button->setParentItem(this);
//                button->setZValue(8);
//                button->show();
//                i++;
//            }
//        }
//    }
}
