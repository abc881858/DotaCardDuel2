#ifndef NET_H
#define NET_H

#include <QJsonObject>
#include <QWebSocket>

#define qNet (Net::instance())

class Net : public QObject
{
    Q_OBJECT

public:
    static Net* instance();
    void initialize();
    void writeToServer(const QJsonObject& jsonObject);
    void writeToServer(const QString &command, const QString &type);
    void writeDeckToServer(const QJsonArray &array, const QString &type);

private:
    QWebSocket* socket;

public slots:
    void connected();
    void readFromServer(const QByteArray& json);

signals:
//    Q_INVOKABLE void set_color_blue();
//    Q_INVOKABLE void set_color_red();

//    Q_INVOKABLE void advise_start_game();
//    Q_INVOKABLE void simulate_start_game();

//    Q_INVOKABLE void advise_shuffle_deck();
//    Q_INVOKABLE void simulate_shuffle_deck(QJsonObject);
//    Q_INVOKABLE void advise_prepare_hand(QJsonObject);
//    Q_INVOKABLE void simulate_prepare_hand();

//    Q_INVOKABLE void advise_draw_phase();
//    Q_INVOKABLE void advise_standby_phase();
//    Q_INVOKABLE void advise_main1_phase();

//    Q_INVOKABLE void simulate_draw_phase();
//    Q_INVOKABLE void simulate_standby_phase();
//    Q_INVOKABLE void simulate_main1_phase();
//    Q_INVOKABLE void simulate_battle_phase();
//    Q_INVOKABLE void simulate_main2_phase();
//    Q_INVOKABLE void simulate_end_phase();
};

#endif // NET_H
