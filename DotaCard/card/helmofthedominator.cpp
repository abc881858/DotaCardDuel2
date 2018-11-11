#include "helmofthedominator.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

HelmOfTheDominator::HelmOfTheDominator()
{
    ISDN = 701;
    name = "HelmOfTheDominator";
    description = tr("HelmOfTheDominator");
}

void HelmOfTheDominator::standby()
{
    EquipSpellCard::standby();
}

void HelmOfTheDominator::activeEffect()
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
