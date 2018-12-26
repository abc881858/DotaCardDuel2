#include "blinkdagger.h"
#include "dota.h"

BlinkDagger::BlinkDagger()
{
    ISDN = 706;
    name = "BlinkDagger";
    description = tr("BlinkDagger");
}

void BlinkDagger::afterEquip()
{
    equipMonsterCard->setCurrentATK(equipMonsterCard->getCurrentATK()+200);
    qDota->resetAtkDef(equipMonsterCard);
}
