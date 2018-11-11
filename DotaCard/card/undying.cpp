#include "undying.h"

Undying::Undying()
{
    ISDN = 608;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Dark_Attribute;
    type = Card::Zombie_Type;
    level = 3;
    ATK = 1100;
    DEF = 1300;
    name = "Undying";
    description = tr("Undying");

    currentATK = ATK;
    currentDEF = DEF;
}
