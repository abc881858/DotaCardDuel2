#ifndef NET_H
#define NET_H

#include <QJsonObject>
#include <QWebSocket>

#if defined(qNet)
#undef qNet
#endif
#define qNet (Net::instance())

class Net : public QObject
{
    Q_OBJECT

public:
    static Net* instance();
    void initialize();
    void write(const QJsonObject& jsonObject);
    void sendMessage(int command);
//    void doAddMyLP(int value);
//    void doAddYourLP(int value);
    void sendDeck(const QVariantList& allISDN);
    void sendEnemyDeck(const QVariantList& allISDN);
    void sendBeAttacked(int sourceIndex, int targetIndex);
    void sendFinishChain();

    void sendBattleAnimationFinished();
    void sendChained(int targetIndex, int areaIndex);

    void moveCard(const QJsonObject& json);
    void sendBeEquiped(int equipSpellCardIndex, int equipMonsterCardIndex);
private:
    QWebSocket* client;

public slots:
    void readFromServer(const QByteArray& json);
    void connected();

signals:
    Q_INVOKABLE void request_moveCard(QJsonObject);

    Q_INVOKABLE void request_setupDeck();
    Q_INVOKABLE void request_enemySetupDeck(QJsonObject);
    Q_INVOKABLE void request_startGame(QJsonObject);
    Q_INVOKABLE void request_enemyStartGame();
    Q_INVOKABLE void request_drawPhase();
    Q_INVOKABLE void request_enemyDrawPhase();
    Q_INVOKABLE void request_standbyPhase();
    Q_INVOKABLE void request_enemyStandbyPhase();
    Q_INVOKABLE void request_main1Phase();
    Q_INVOKABLE void request_enemyMain1Phase();
    Q_INVOKABLE void request_endPhase();
    Q_INVOKABLE void request_enemyEndPhase();
    Q_INVOKABLE void request_enemyBattlePhase();
    Q_INVOKABLE void request_enemyMain2Phase();

    Q_INVOKABLE void request_enemyBeAttack(QJsonObject);
    Q_INVOKABLE void request_finishChain();

    Q_INVOKABLE void request_enemyChained(QJsonObject);
    Q_INVOKABLE void request_enemyBeEquiped(QJsonObject);
};

#endif // NET_H
