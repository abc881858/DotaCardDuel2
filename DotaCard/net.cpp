#include "net.h"
#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QUrl>

Q_GLOBAL_STATIC(Net, net)

Net* Net::instance()
{
    return net();
}

void Net::initialize()
{
    client = new QWebSocket;
    client->open(QUrl("ws://localhost:7720")); //QUrl("ws://139.196.72.104:7720")
    connect(client, SIGNAL(connected()), this, SLOT(connected()));
    connect(client, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(readFromServer(QByteArray)));
}

void Net::write(QJsonObject jsonObject)
{
    QJsonDocument jsonDoucment(jsonObject);
    QByteArray byteArray = jsonDoucment.toJson(QJsonDocument::Compact); //压缩的json
    client->sendBinaryMessage(byteArray);
//    qDebug() << "write: " << jsonObject;
}

void Net::connected()
{
    QJsonObject jsonObject;
    jsonObject.insert("command", 1000);
    write(jsonObject);
}

void Net::readFromServer(QByteArray json)
{
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(json);
    QJsonObject object = jsonDoucment.object();
//    qDebug() << "Net's readFromServer" << object;

    QString request = object["request"].toString();
    if (request.isEmpty())
    {
        return;
    }
    else
    {
        request.prepend("request_");
        QJsonObject parameter = object["parameter"].toObject();
        if (parameter.isEmpty())
        {
            QMetaObject::invokeMethod(this, request.toLatin1().data());
        }
        else
        {
            QMetaObject::invokeMethod(this, request.toLatin1().data(), Q_ARG(QJsonObject, parameter));
        }
    }
}

void Net::sendMessage(int command)
{
    QJsonObject jsonObject;
    jsonObject.insert("command", command);
    write(jsonObject);
}

void Net::sendDeck(QVariantList allISDN)
{
    QJsonArray array = QJsonArray::fromVariantList(allISDN);
    QJsonObject jsonObject;
    jsonObject.insert("command", 2000);
    jsonObject.insert("array", array);
    write(jsonObject);
}

void Net::sendEnemyDeck(QVariantList allISDN)
{
    QJsonArray array = QJsonArray::fromVariantList(allISDN);
    QJsonObject jsonObject;
    jsonObject.insert("command", 2001);
    jsonObject.insert("array", array);
    write(jsonObject);
}

void Net::sendDraw()
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemyDrawFirst"));
    write(jsonObject);
}

void Net::sendSpecialSummon(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemySpecialSummon"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}

void Net::sendSummon(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemySummon"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}

void Net::sendActive(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemyActive"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}

void Net::sendSet(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemySet"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}

void Net::sendDeclared(int sourceIndex, int targetIndex)
{
    QJsonObject parameter;
    parameter.insert("sourceIndex", sourceIndex);
    parameter.insert("targetIndex", targetIndex);
    QJsonObject object;
    object.insert("request", QString("enemyDeclared"));
    object.insert("parameter", parameter);
    Net::instance()->write(object);
}

void Net::sendChained(int targetIndex, int areaIndex)
{
    QJsonObject parameter;
    parameter.insert("targetIndex", targetIndex);
    parameter.insert("areaIndex", areaIndex);
    QJsonObject object;
    object.insert("request", QString("enemyChained"));
    object.insert("parameter", parameter);
    Net::instance()->write(object);
}

void Net::sendFinishChain()
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("finishChain"));
    write(jsonObject);
}

void Net::sendDestroyEnemyFieldyard(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("destroyFieldyard"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}

void Net::sendDestroyFieldyard(int index)
{
    QJsonObject jsonObject;
    jsonObject.insert("request", QString("enemyDestroyFieldyard"));
    QJsonObject parameter;
    parameter.insert("index", index);
    jsonObject.insert("parameter", parameter);
    write(jsonObject);
}
