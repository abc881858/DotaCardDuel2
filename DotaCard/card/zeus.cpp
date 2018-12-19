#include "zeus.h"
#include "dota.h"

Zeus::Zeus()
{
    ISDN = 610;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Light_Attribute;
    type = Card::Spellcaster_Type;
    level = 2;
    ATK = 500;
    DEF = 350;
    name = "Zeus";
    description = tr("Zeus");

    currentATK = ATK;
    currentDEF = DEF;
}

bool Zeus::testSpecialSummon()
{
    if(qDota->hasMonster())
    {
        return true;
    }
    return false;
}
