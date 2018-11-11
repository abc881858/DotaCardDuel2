#include "lion.h"

Lion::Lion()
{
    ISDN = 603;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Dark_Attribute;
    type = Card::Fiend_Type;
    level = 4;
    ATK = 1300;
    DEF = 700;
    name = "Lion";
    description = tr("Lion");

    currentATK = ATK;
    currentDEF = DEF;
}
