#include "helmofthedominator.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

HelmOfTheDominator::HelmOfTheDominator()
{
    ISDN = 701;
    name = "HelmOfTheDominator";
    description = tr("HelmOfTheDominator");
    canEffect = true;
}

void HelmOfTheDominator::standby()
{
    EquipSpellCard::standby();
    canEffect = true;
}

bool HelmOfTheDominator::testEffectFromFieldground()
{
    if(area != Card::Fieldground_Area)
    {
        return false;
    }

    //一回合一次，选择自己卡组的一只3星以下的怪兽特殊召唤。
    //当这张装备卡从场上离开或再次使用该效果时，召唤怪兽破坏。
    if (qDota->phase == Dota::Main1_Phase ||
            qDota->phase == Dota::Main2_Phase)
    {
        if(canEffect)
        {
            return true;
        }
    }
    return false;
}

void HelmOfTheDominator::active()
{
    qDebug() << "active HelmOfTheDominator";
    canEffect = false;
}

void HelmOfTheDominator::activeAfterEquiped()
{
    equipMonsterCard->setCurrentDEF(equipMonsterCard->getCurrentDEF()+300);
}
