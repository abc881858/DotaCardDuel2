#include "gemoftruesight.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

GemOfTrueSight::GemOfTrueSight()
{
    ISDN = 703;
    name = "GemOfTrueSight";
    description = tr("GemOfTrueSight");
}

void GemOfTrueSight::standby()
{
    EquipSpellCard::standby();
}

void GemOfTrueSight::activeEffect()
{
//    int result = testEffectFromFieldyard();
//    if(result == 3)
//    {
//        QMessageBox::StandardButton ret;
//        ret = QMessageBox::question(nullptr, QString(tr("active CentaurWarrunner's effect")), QString(tr("select effect1 or effect2?")), QMessageBox::Yes | QMessageBox::No);

//    }

    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(nullptr, QString(tr("active CentaurWarrunner's effect")), QString(tr("Select all atk or all def?")), QMessageBox::Yes | QMessageBox::No);
//    bool all = (ret == QMessageBox::Yes);
//    for (Card* card : qDota->fieldyardCards)
//    {
//        if (card->getFace())
//        {
//            card->setStand(all);
//        }
//    }

//QJsonObject parameter;
//parameter.insert("pickRequirement", CentaurWarrunnerEffect);
//parameter.insert("all", all);
//QJsonObject object;
//object.insert("request", "Effect");
//object.insert("parameter", parameter);
//Net::instance()->write(object);
}
