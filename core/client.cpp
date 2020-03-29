#include "client.h"
#include "net.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "engine.h"
#include "room.h"

Q_GLOBAL_STATIC(Client, client)

Client* Client::instance()
{
    return client();
}

void Client::initialize()
{
    //
}

void Client::setPhase(PhaseFlag phase)
{
    m_phase = phase;
}

Client::PhaseFlag Client::phase() const
{
    return m_phase;
}

void Client::setColor(ColorFlag color)
{
    m_color = color;
}

Client::ColorFlag Client::color() const
{
    return m_color;
}

void Client::setStatus(StatusFlag status)
{
    m_status = status;
}

Client::StatusFlag Client::status() const
{
    return m_status;
}

void Client::set_color_blue()
{
    m_color = Blue_Color;
    qDebug() << "i am blue client";
}

void Client::set_color_red()
{
    m_color = Red_Color;
    qDebug() << "i am red client";
}

void Client::advise_start_game()
{
    qDebug() << "---advise_start_game---";
    Q_ASSERT(m_color == Blue_Color);

    //animation about start game
    qDebug() << "show blue start game animation";

    qNet->writeToServer("start_game", "command_copy");
}

void Client::simulate_start_game()
{
    qDebug() << "---simulate_start_game---";
    Q_ASSERT(m_color == Red_Color);

    //animation about start game
    qDebug() << "show red start game animation";

    qNet->writeToServer("start_game", "command_over");
}

void Client::advise_shuffle_deck()
{
    qDebug() << "---advise_shuffle_deck---";
    //animation about shuffle deck

    QJsonArray allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QJsonValue(ISDN);
        Card* card = qEngine->cloneCard(ISDN);
        deckCards << card;
    }
    file.close();
    qDebug() << "setup local deck:" << allISDN;

    qRoom->setup_local_deck(deckCards);
    qNet->writeDeckToServer(allISDN, "command_copy");
}

void Client::simulate_shuffle_deck(QJsonObject parameter)
{
    qDebug() << "---simulate_shuffle_deck---";
    //animation about shuffle remote deck

    QJsonArray array = parameter["deck"].toArray();
    for(QJsonValue value : array)
    {
        Card *card = qEngine->cloneCard(value.toInt());
        card->setArea(Card::Remote_Deck_Area);
        remoteDeckCards << card;
    }
    qDebug() << "setup remote deck:" << array;
    qRoom->setup_remote_deck(remoteDeckCards);

    //animation about shuffle local deck

    QJsonArray allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QJsonValue(ISDN);
        Card* card = qEngine->cloneCard(ISDN);
        deckCards << card;
    }
    file.close();
    qDebug() << "setup local deck:" << allISDN;

    qRoom->setup_local_deck(deckCards);
    qNet->writeDeckToServer(allISDN, "command_over");
}

void Client::drawDeckCard()
{
    Card* firstCard = deckCards.takeLast();
    handCards << firstCard;
    qDebug() << "draw first card from deck to hand";
    CardMoveStruct card_move;
    card_move.areaFrom = Card::Deck_Area;
    card_move.areaTo = Card::Hand_Area;
    qRoom->move_card_item(card_move);

    //animation
}

void Client::drawDeckCard(int num)
{
    for(int i=0; i<num; i++)
    {
        drawDeckCard();
    }
}

void Client::advise_prepare_hand(QJsonObject parameter)
{
    qDebug() << "---advise_prepare_hand---";
    //animation about shuffle remote deck

    QJsonArray array = parameter["deck"].toArray();
    for(QJsonValue value : array)
    {
        Card *card = qEngine->cloneCard(value.toInt());
        card->setArea(Card::Remote_Deck_Area);
        remoteDeckCards << card;
    }
    qDebug() << "setup remote deck:" << array;
    qRoom->setup_remote_deck(remoteDeckCards);

    drawDeckCard(5);

    qNet->writeToServer("prepare_hand", "command_copy");
}

void Client::simulate_drawDeckCard()
{
    Card* firstCard = remoteDeckCards.takeLast();
    remoteHandCards << firstCard;
    qDebug() << "draw first card from remoteDeck to remoteHand";

    //animation
}

void Client::simulate_drawDeckCard(int num)
{
    for(int i=0; i<num; i++)
    {
        simulate_drawDeckCard();
    }
}

void Client::simulate_prepare_hand()
{
    qDebug() << "---simulate_prepare_hand---";
    if(m_color == Red_Color)
    {
        simulate_drawDeckCard(5);
        drawDeckCard(5);
        qNet->writeToServer("prepare_hand", "command_copy");
    }
    else if(m_color == Blue_Color)
    {
        simulate_drawDeckCard(5);

        //go to Phase Circle finally
        advise_draw_phase();
    }
}

void Client::advise_draw_phase()
{
    qDebug() << "---advise_draw_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Draw_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Draw_Phase;
    }
    drawDeckCard();
    qNet->writeToServer("draw_phase", "command_copy");
}

void Client::advise_standby_phase()
{
    qDebug() << "---advise_standby_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Standby_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Standby_Phase;
    }
    //animation
    //......
    qNet->writeToServer("standby_phase", "command_copy");
}

void Client::advise_main1_phase()
{
    qDebug() << "---advise_main1_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Main1_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Main1_Phase;
    }
    //animation
    //......
    qNet->writeToServer("main1_phase", "command_copy");
}

void Client::simulate_draw_phase()
{
    qDebug() << "---simulate_draw_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Draw_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Draw_Phase;
    }
    //do somthing
    simulate_drawDeckCard();
    qNet->writeToServer("draw_phase", "command_over");
}

void Client::simulate_standby_phase()
{
    qDebug() << "---simulate_standby_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Standby_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Standby_Phase;
    }
    //do somthing
    //......
    qNet->writeToServer("standby_phase", "command_over");
}

void Client::simulate_main1_phase()
{
    qDebug() << "---simulate_main1_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Main1_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Main1_Phase;
    }
    //do somthing
    //......
    qNet->writeToServer("main1_phase", "command_over");
}

void Client::simulate_battle_phase()
{
    qDebug() << "---simulate_battle_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Battle_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Battle_Phase;
    }
    //do somthing
    //......
    qNet->writeToServer("battle_phase", "command_over");
}

void Client::simulate_main2_phase()
{
    qDebug() << "---simulate_main2_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_Main2_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_Main2_Phase;
    }
    //do somthing
    //......
    qNet->writeToServer("main2_phase", "command_over");
}

void Client::simulate_end_phase()
{
    qDebug() << "---simulate_end_phase---";
    if(m_color == Blue_Color)
    {
        m_phase = Blue_End_Phase;
    }
    else if(m_color == Red_Color)
    {
        m_phase = Red_End_Phase;
    }
    //do somthing
    //......
    qNet->writeToServer("end_phase", "command_over");
}
