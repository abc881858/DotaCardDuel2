#include "magnus.h"

Magnus::Magnus()
{
    ISDN = 604;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Earth_Attribute;
    type = Card::BeastWarrior_Type;
    level = 4;
    ATK = 1700;
    DEF = 700;
    name = "Magnus";
    description = tr("Magnus");

    currentATK = ATK;
    currentDEF = DEF;
}
