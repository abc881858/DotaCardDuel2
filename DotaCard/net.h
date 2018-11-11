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
    void write(QJsonObject jsonObject);
    void sendMessage(int command);
//    void doAddMyLP(int value);
//    void doAddYourLP(int value);
    void sendDeck(QVariantList allISDN);
    void sendEnemyDeck(QVariantList allISDN);
    void sendDeclared(int sourceIndex, int targetIndex);
    void sendDraw();
    void sendSpecialSummon(int index);
    void sendSummon(int index);
    void sendActive(int index);
    void sendSet(int index);
    void sendFinishChain();

    void sendDestroyEnemyFieldyard(int index);
    void sendDestroyFieldyard(int index);
    void sendBattleAnimationFinished();
    void sendChained(int targetIndex, int areaIndex);
private:
    QWebSocket* client;

public slots:
    void readFromServer(QByteArray json);
    void connected();

signals:
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
    Q_INVOKABLE void request_enemyDrawFirst();
    Q_INVOKABLE void request_enemySpecialSummon(QJsonObject);
    Q_INVOKABLE void request_enemySummon(QJsonObject);
    Q_INVOKABLE void request_enemyActive(QJsonObject);
    Q_INVOKABLE void request_enemySet(QJsonObject);
    Q_INVOKABLE void request_enemyDeclared(QJsonObject);
    Q_INVOKABLE void request_finishChain();
    Q_INVOKABLE void request_destroyFieldyard(QJsonObject);
    Q_INVOKABLE void request_enemyDestroyFieldyard(QJsonObject);
    Q_INVOKABLE void request_enemyChained(QJsonObject);
};

#endif // NET_H
