#include "aghanimsscepter.h"
#include "dota.h"

AghanimsScepter::AghanimsScepter()
{
    ISDN = 707;
    name = "AghanimsScepter";
    description = tr("AghanimsScepter");
}

void AghanimsScepter::afterEquip()
{
    equipMonsterCard->setCurrentATK(equipMonsterCard->getCurrentATK()+400);
    equipMonsterCard->setCurrentDEF(equipMonsterCard->getCurrentDEF()+700);
    qDota->resetAtkDef(equipMonsterCard);
}
