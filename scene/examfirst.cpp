#include "examfirst.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "view.h"
#include "engine.h"
#include "client.h"
#include <QTimer>
#include <QPropertyAnimation>

#define LeftPos QPointF(0,0)
#define RightPos QPointF(230,0)

#define DeckPos QPointF(732, 441)
#define HandPos QPointF(19+256, 529)
#define FieldyardPos QPointF(94+256, 317)
#define FieldgroundPos QPointF(94+256, 424)
#define GraveyardPos QPointF(485+256, 330)
#define EnemyDeckPos QPointF(270, 93)
#define EnemyHandPos QPointF(17+256, -71)
#define EnemyFieldyardPos QPointF(78+256, 213)
#define EnemyFieldgroundPos QPointF(80+256, 105)
#define EnemyGraveyardPos QPointF(15+256, 200)

Q_GLOBAL_STATIC(ExamFirst, examFirst)

ExamFirst* ExamFirst::instance()
{
    return examFirst();
}

void ExamFirst::initialize()
{
    background = new Spirit(":/exam1/0");
    addItem(background);
    background->setPos(0,0);

    bigImage = new Spirit(":/info/NULL");
    addItem(bigImage);
    bigImage->setPos(2,74);

    ai_shuffle = new Gif(QStringList() << ":/exam1/1" << ":/exam1/2" << ":/exam1/3" << ":/exam1/4" << ":/exam1/5");
    ai_shuffle->setPos(300,200);
    addItem(ai_shuffle);
    ai_shuffle->hide();
    connect(ai_shuffle, &Gif::finished, this, &ExamFirst::ai_shuffle_finished);

    i_shuffle = new Gif(QStringList() << ":/exam1/1" << ":/exam1/2" << ":/exam1/3" << ":/exam1/4" << ":/exam1/5");
    i_shuffle->setPos(600,300);
    addItem(i_shuffle);
    i_shuffle->hide();
    connect(i_shuffle, &Gif::finished, this, &ExamFirst::i_shuffle_finished);

    black = new BlackScreen;
    addItem(black);
    connect(black, &BlackScreen::show_over, this, &ExamFirst::show_over);
    connect(black, &BlackScreen::hide_over, this, &ExamFirst::hide_over);
}

void ExamFirst::showScene()
{
    qView->setScene(this);
    black->showAnimation();
}

void ExamFirst::show_over()
{
//    button_1->setEnabled(true);
//    button_2->setEnabled(true);
//    button_3->setEnabled(true);
//    button_4->setEnabled(true);
//    button_5->setEnabled(true);
//    button_6->setEnabled(true);

    //start game......
    QList<int> ai_deck{2,2,2,2,2,2,2,2,2,2};
    for (int ISDN : ai_deck)
    {
        Card *card = qEngine->cloneCard(ISDN);
        remoteDeckCards << card;
    }
    setup_remote_deck(remoteDeckCards);

    QList<int> my_deck{1,1,1,1,1,1,1,1,1,17};
    for (int ISDN : my_deck)
    {
        Card *card = qEngine->cloneCard(ISDN);
        deckCards << card;
    }
    setup_local_deck(deckCards);

    //shuffle animation
    ai_shuffle->show_animation();
}

void ExamFirst::ai_shuffle_finished()
{
    i_shuffle->show_animation();
}

void ExamFirst::i_shuffle_finished()
{
    //first AI draw 5 cards animation
    for(int i=0; i<5; i++)
    {
        Card* firstCard = remoteDeckCards.takeLast();
        remoteHandCards << firstCard;
        CardMoveStruct card_move;
        card_move.areaFrom = Card::Remote_Deck_Area;
        card_move.areaTo = Card::Remote_Hand_Area;
        move_card_item(card_move);
    }
    //second I draw 5 cards animation
    for(int i=0; i<5; i++)
    {
        Card* firstCard = deckCards.takeLast();
        handCards << firstCard;
        CardMoveStruct card_move;
        card_move.areaFrom = Card::Deck_Area;
        card_move.areaTo = Card::Hand_Area;
        move_card_item(card_move);
    }
//        enemy_draw_card_animation
}

void ExamFirst::hideScene()
{
//    button_1->setEnabled(false);
//    button_2->setEnabled(false);
//    button_3->setEnabled(false);
//    button_4->setEnabled(false);
//    button_5->setEnabled(false);
//    button_6->setEnabled(false);
    black->hideAnimation();
}

void ExamFirst::hide_over()
{
    int index = button_index;
    button_index = -1;
    switch (index)
    {
    case -1:
        break;
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}

void ExamFirst::setup_local_deck(QList<Card*> deckCards)
{
    qDebug() << "Room::setup_local_deck ";
    for(Card* card : deckCards)
    {
        CardItem *item = new CardItem(card);
        connect(item, &CardItem::update_big_image, this, &ExamFirst::update_big_image);
        item->setPlace(CardItem::Deck_Place);
        item->changeImage();
        deckItems << item;
        addItem(item);
        int index = deckItems.size();
        item->setPos(DeckPos+QPointF(0.2*index,-0.2*index));
        item->setZValue(10+index);
    }
}

void ExamFirst::setup_remote_deck(QList<Card*> remoteDeckCards)
{
    qDebug() << "Room::setup_remote_deck ";
    for(Card* card : remoteDeckCards)
    {
        CardItem *item = new CardItem(card);
        connect(item, &CardItem::update_big_image, this, &ExamFirst::update_big_image);
        item->setPlace(CardItem::Remote_Deck_Place);
        item->changeImage();
        remoteDeckItems << item;
        addItem(item);
        int index = remoteDeckItems.size();
        item->setPos(EnemyDeckPos+QPointF(-0.2*index,0.2*index));
        item->setZValue(10+index);
    }
}

void ExamFirst::adjustHandItems()
{
    if (handItems.isEmpty())
        return;
    int n = handItems.size();
    int card_skip = (n > 5) ? (412 / (n - 1)) : 102;
    for (int i = 0; i < n; i++)
    {
        handItems[i]->setZValue(100 + 0.1 * i);
        handItems[i]->setPos(HandPos + QPointF(card_skip * i, 0));
    }
}

void ExamFirst::adjustRemoteHandItems(CardItem* item)
{
    if (remoteHandItems.isEmpty())
        return;
    int n = remoteHandItems.size();
    int card_skip = (n > 5) ? (412 / (n - 1)) : 102;
    for (int i = 0; i < n; i++)
    {
        remoteHandItems[i]->setZValue(100 + 0.1 * i);
//        if(remoteHandItems[i]==item)
//        {
//            auto draw_animation = new QPropertyAnimation(item, "pos");
//            draw_animation->setStartValue(item->pos());
//            draw_animation->setEndValue(EnemyHandPos + QPointF(408 - card_skip * i, 0));
//            draw_animation->setDuration(1000);
//            draw_animation->start(QAbstractAnimation::DeleteWhenStopped);
//        }
//        else
//        {
            remoteHandItems[i]->setPos(EnemyHandPos + QPointF(408 - card_skip * i, 0));
//        }
    }
}

void ExamFirst::move_card_item(CardMoveStruct card_move)
{
    CardItem *item = nullptr;
    int indexFrom = card_move.indexFrom;
    int indexTo = card_move.indexTo;

    switch (card_move.areaFrom)
    {
    case Card::Deck_Area:
        item = deckItems.takeLast();
        break;
    case Card::Hand_Area:
        item = handItems.takeAt(indexFrom);
        adjustHandItems();
        break;
    case Card::Front_Area:
        item = frontItems[indexFrom];
        frontItems[indexFrom] = nullptr;
//        word[indexFrom].hide();
        break;
    case Card::Back_Area:
        item = backItems[indexFrom];
        backItems[indexFrom] = nullptr;
        break;
    case Card::Grave_Area:
        item = graveItems.takeAt(indexFrom);
        break;

    case Card::Remote_Deck_Area:
        item = remoteDeckItems.takeLast();
        break;
    case Card::Remote_Hand_Area:
        item = remoteHandItems.takeAt(indexFrom);
        adjustRemoteHandItems(item);
        break;
    case Card::Remote_Front_Area:
        item = remoteFrontItems[indexFrom];
        remoteFrontItems[indexFrom] = nullptr;
//        word[5+indexFrom].hide();
        break;
    case Card::Remote_Back_Area:
        item = remoteBackItems[indexFrom];
        remoteBackItems[indexFrom] = nullptr;
        break;
    case Card::Remote_Grave_Area:
        item = remoteGraveItems.takeAt(indexFrom);
        break;
    default:
        // for No_Area
        break;
    }

    switch (card_move.areaTo)
    {
    case Card::Deck_Area:
        deckItems << item;
        item->setPlace(CardItem::Deck_Place);
        item->setPos(DeckPos);
        item->setZValue(10+deckItems.size());
        break;
    case Card::Hand_Area:
        handItems << item;
        item->setPlace(CardItem::Hand_Place);
        adjustHandItems();
        break;
    case Card::Front_Area:
    {
        frontItems[indexTo] = item;
        frontItems[indexTo]->setPlace(CardItem::Front_Place);
        item->setPos(350+78*indexTo, 317);
        item->setZValue(2);
//        word[indexTo].setPlainText(QString("%1 / %2").arg(qDota->getAtkFromIndex(indexTo)).arg(qDota->getDefFromIndex(indexTo)));
//        word[indexTo].show();
        break;
    }
    case Card::Back_Area:
    {
        backItems[indexTo] = item;
        backItems[indexTo]->setPlace(CardItem::Back_Place);
        item->setPos(350+78*indexTo, 424);
        item->setZValue(2);
        break;
    }
    case Card::Grave_Area:
        graveItems << item;
        item->setPlace(CardItem::Grave_Place);
        item->setPos(GraveyardPos);
        item->setZValue(graveItems.size());
        break;
    case Card::Remote_Deck_Area:
        remoteDeckItems << item;
        item->setPlace(CardItem::Remote_Deck_Place);
        item->setPos(EnemyDeckPos);
        item->setZValue(10+remoteDeckItems.size());
        break;
    case Card::Remote_Hand_Area:
        remoteHandItems << item;
        item->setPlace(CardItem::Remote_Hand_Place);
        adjustRemoteHandItems(item);
        break;
    case Card::Remote_Front_Area:
    {
        remoteFrontItems[indexTo] = item;
        remoteFrontItems[indexTo]->setPlace(CardItem::Remote_Front_Place);
        item->setPos(EnemyFieldyardPos + QPointF(320 - 78 * indexTo, 0));
        item->setZValue(2);
//        word[5+indexTo].setPlainText(QString("%1 / %2").arg(qDota->getAtkFromIndex(indexTo,true)).arg(qDota->getDefFromIndex(indexTo,true)));
//        word[5+indexTo].show();
        break;
    }
    case Card::Remote_Back_Area:
    {
        remoteBackItems[indexTo] = item;
        remoteBackItems[indexTo]->setPlace(CardItem::Remote_Back_Place);
        item->setPos(EnemyFieldgroundPos + QPointF(320 - 78 * indexTo, 0));
        item->setZValue(2);
        break;
    }
    case Card::Remote_Grave_Area:
        remoteGraveItems << item;
        item->setPlace(CardItem::Remote_Grave_Place);
        item->setPos(EnemyGraveyardPos);
        item->setZValue(remoteGraveItems.size());
        break;
    default:
        // for No_Area
        break;
    }

    item->changeImage(); // Todo: 改到card里
//    item->clearFinger(); // Todo: 改到card里
}

void ExamFirst::update_big_image(QString fileNameLarge)
{
    bigImage->setPixmap(fileNameLarge);
    //首先一张卡被hover，左上角大图肯定要更新
    //但对方的（除前后场的face-up卡）不该显示，我方卡组也不该显示
    bigImage->update();
    //    textedit->setText(item->getDescription());
}
