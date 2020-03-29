#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <card.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define qClient (Client::instance())

class Client : public QObject
{
    Q_OBJECT

public:
    enum PhaseFlag
    {
        No_Phase,
        Blue_Draw_Phase,
        Blue_Standby_Phase,
        Blue_Main1_Phase,
        Blue_Battle_Phase,
        Blue_Main2_Phase,
        Blue_End_Phase,
        Red_Draw_Phase,
        Red_Standby_Phase,
        Red_Main1_Phase,
        Red_Battle_Phase,
        Red_Main2_Phase,
        Red_End_Phase
    };
    Q_ENUM(PhaseFlag)

    enum ColorFlag
    {
        No_Color,
        Blue_Color,
        Red_Color,
        Yellow_Color,
        Green_Color
    };
    Q_ENUM(ColorFlag)

    enum StatusFlag
    {
        No_Status,
//        Prepare_Status,
        Working_Status,
        Waiting_Status
    };
    Q_ENUM(StatusFlag)

    static Client* instance();
    void initialize();

    void setupDeckCard();

    void setPhase(Client::PhaseFlag phase);
    PhaseFlag phase() const;

    void setColor(Client::ColorFlag color);
    ColorFlag color() const;

    void setStatus(Client::StatusFlag status);
    StatusFlag status() const;

    void drawDeckCard(int num);
    void drawDeckCard();

    void simulate_drawDeckCard(int num);
    void simulate_drawDeckCard();

public:
    Q_INVOKABLE void set_color_blue();
    Q_INVOKABLE void set_color_red();

    Q_INVOKABLE void advise_start_game();
    Q_INVOKABLE void simulate_start_game();

    Q_INVOKABLE void advise_shuffle_deck();
    Q_INVOKABLE void simulate_shuffle_deck(QJsonObject parameter);
    Q_INVOKABLE void advise_prepare_hand(QJsonObject parameter);
    Q_INVOKABLE void simulate_prepare_hand();

    Q_INVOKABLE void advise_draw_phase();
    Q_INVOKABLE void advise_standby_phase();
    Q_INVOKABLE void advise_main1_phase();

    Q_INVOKABLE void simulate_draw_phase();
    Q_INVOKABLE void simulate_standby_phase();
    Q_INVOKABLE void simulate_main1_phase();
    Q_INVOKABLE void simulate_battle_phase();
    Q_INVOKABLE void simulate_main2_phase();
    Q_INVOKABLE void simulate_end_phase();

private:
    PhaseFlag m_phase{No_Phase};
    ColorFlag m_color{No_Color};
    StatusFlag m_status{No_Status};

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
};

#endif // CLIENT_H
