#include "vengefulspirit.h"

VengefulSpirit::VengefulSpirit()
{
    ISDN = 609;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Dark_Attribute;
    type = Card::Fairy_Type;
    level = 3;
    ATK = 1200;
    DEF = 500;
    name = "VengefulSpirit";
    description = tr("VengefulSpirit");

    currentATK = ATK;
    currentDEF = DEF;
}
