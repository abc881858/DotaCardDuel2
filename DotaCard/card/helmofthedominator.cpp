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
    didEffect = false;
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
    qDebug() << "try active HelmOfTheDominator";

    canEffect = false;

    qDota->currentActiveCard = this;
    qDota->whoIsDoing = false;
    emit qDota->showWarningDialog();
}

void HelmOfTheDominator::doActive()
{
    if(didEffect)
    {
        //召唤怪兽破坏
    }
    else
    {
        didEffect = true;
    }
    qDota->doActive(); //显示 dialog3 特招对话框
}

void HelmOfTheDominator::unActive()
{
    canEffect = true;
    qDota->currentActiveCard = nullptr;
}

void HelmOfTheDominator::afterEquip()
{
    equipMonsterCard->setCurrentDEF(equipMonsterCard->getCurrentDEF()+300);
}
