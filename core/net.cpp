#include "net.h"
#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QUrl>
#include "client.h"

Q_GLOBAL_STATIC(Net, net)

Net* Net::instance()
{
    return net();
}

void Net::initialize()
{
    socket = new QWebSocket;
    socket->open(QUrl("ws://localhost:7720"));
    //    socket->open(QUrl("ws://47.101.204.243:7720"));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readFromServer(QByteArray)));
}

void Net::connected()
{
    qDebug() << "socket connected server";
}

void Net::readFromServer(const QByteArray& json)
{
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(json);
    QJsonObject object = jsonDoucment.object();
    QString command = object["command"].toString();
    QString type = object["type"].toString();
    if(type == "command_advise")
    {
        command.prepend("advise_");
    }
    else if(type == "command_simulate")
    {
        command.prepend("simulate_");
    }
    else if(type == "command_set")
    {
        command.prepend("set_");
    }
    QJsonObject parameter = object["parameter"].toObject();
    if (parameter.isEmpty())
    {
        QMetaObject::invokeMethod(qClient, command.toLatin1().data());
    }
    else
    {
        QMetaObject::invokeMethod(qClient, command.toLatin1().data(), Q_ARG(QJsonObject, parameter));
    }
}

void Net::writeToServer(const QJsonObject &jsonObject)
{
    QJsonDocument jsonDoucment(jsonObject);
    QByteArray byteArray = jsonDoucment.toJson(QJsonDocument::Compact); //压缩的json
    socket->sendBinaryMessage(byteArray);
}

void Net::writeToServer(const QString &command, const QString &type)
{
    QJsonObject jsonObject;
    jsonObject.insert("command", command);
    jsonObject.insert("type", type);

    writeToServer(jsonObject);
}

void Net::writeDeckToServer(const QJsonArray &array, const QString &type)
{
    QJsonObject jsonObject;
    jsonObject.insert("command", "shuffle_deck");
    jsonObject.insert("type", type);
    jsonObject.insert("deck", array);

    writeToServer(jsonObject);
}
