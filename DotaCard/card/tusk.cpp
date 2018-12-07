#include "tusk.h"

Tusk::Tusk()
{
    ISDN = 607;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Water_Attribute;
    type = Card::BeastWarrior_Type;
    level = 4;
    ATK = 1800;
    DEF = 1000;
    name = "Tusk";
    description = tr("Tusk");

    currentATK = ATK;
    currentDEF = DEF;
}
