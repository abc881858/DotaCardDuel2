#include "deckscene.h"

//#include <QIcon>
//#include <QFile>
//#include "engine.h"
//#include "card.h"

DeckScene::DeckScene(QObject* parent)
    : QGraphicsScene(parent)
{
    leftarea = new Pixmap(":/png/zujiankazu2");
    addItem(leftarea);
    leftarea->setPos(0,0);

    leftarea->setCursor(QCursor(QPixmap(":/cursor/cur3"),31,15));

    listwidget = new QListWidget;
    proxywidget = addWidget(listwidget);
    proxywidget->setPos(690,40);
    proxywidget->resize(80,550);

    listwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listwidget->setIconSize(QSize(43,50));
    listwidget->setStyleSheet("QListWidget{color: rgb(67, 209, 243); font: bold 12px 宋体;}"); //  font-weight:400; font-style:normal; border: 2px; padding: 2px; margin:2px;

    listwidget->setSelectionMode(QAbstractItemView::NoSelection);

//    QFile file("test1.txt");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    QTextStream text_stream(&file);
//    while (!text_stream.atEnd())
//    {
//        int ISDN = text_stream.readLine().toInt();
//        Card* card = Engine::instance()->cloneCard(ISDN);

//        QListWidgetItem *item = new QListWidgetItem;
//        item->setBackground(QBrush(QPixmap(":/png/png/list_item2.png")));
//        item->setSizeHint(QSize(79,52));
//        item->setIcon(QIcon(QPixmap(QString(":/allcards/%1.jpg", card->getName()))));
//        if(card->isMonstor())
//        {
//            item->setText(QString("%1\n%2").arg(card->getATK(), card->getDEF()));
//            item->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
//        }
//        listwidget->addItem(item);
//    }
//    file.close();
}

void DeckScene::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}
