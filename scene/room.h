#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>
#include "carditem.h"
#include <QGraphicsPixmapItem>
#include "blackscreen.h"

#define qRoom (Room::instance())

class Room : public QGraphicsScene
{
    Q_OBJECT

public:
    static Room* instance();
    void initialize();
    Spirit *background;
    Spirit *bigImage;

    void update_big_image(QString fileNameLarge);
    void setup_local_deck(QList<Card *> deckCards);
    void setup_remote_deck(QList<Card *> remoteDeckCards);
    void move_card_item(CardMoveStruct card_move);
    void adjustHandItems();
    void adjustRemoteHandItems();

    BlackScreen *black;
    void showScene();
    void hideScene();

private:
    QList<CardItem*> deckItems;
    QList<CardItem*> handItems;
    CardItem* frontItems[5]{};
    CardItem* backItems[5]{};
    QList<CardItem*> graveItems;

    QList<CardItem*> remoteDeckItems;
    QList<CardItem*> remoteHandItems;
    CardItem* remoteFrontItems[5]{};
    CardItem* remoteBackItems[5]{};
    QList<CardItem*> remoteGraveItems;
};

#endif // ROOM_H
