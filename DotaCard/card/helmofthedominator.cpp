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
