#ifndef EXAMFIRST_H
#define EXAMFIRST_H

#include <QGraphicsScene>
#include "carditem.h"
#include <QGraphicsPixmapItem>
#include "blackscreen.h"
#include "gif.h"

#define qExamFirst (ExamFirst::instance())

class ExamFirst : public QGraphicsScene
{
    Q_OBJECT

public:
    static ExamFirst* instance();
    void initialize();
    Spirit *background;
    Spirit *bigImage;
    Gif *i_shuffle;
    Gif *ai_shuffle;

//    Button *button_1;
//    Button *button_2;
//    Button *button_3;
//    Button *button_4;
//    Button *button_5;
//    Button *button_6;

    void setup_local_deck(QList<Card *> deckCards);
    void setup_remote_deck(QList<Card *> remoteDeckCards);
    void move_card_item(CardMoveStruct card_move);
    void adjustHandItems();
    void adjustRemoteHandItems(CardItem *item);

    BlackScreen *black;
    void showScene();

private:
    int button_index{-1};
    void hideScene();

    QList<Card*> deckCards;
    QList<Card*> handCards;
    Card* frontCards[5];
    Card* backCards[5];
    QList<Card*> graveCards;

    QList<Card*> remoteDeckCards;
    QList<Card*> remoteHandCards;
    Card* remoteFrontCards[5];
    Card* remoteBackCards[5];
    QList<Card*> remoteGraveCards;

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

public slots:
    void show_over();
    void hide_over();
    void update_big_image(QString fileNameLarge);
    void ai_shuffle_finished();
    void i_shuffle_finished();
};

#endif // EXAMFIRST_H
