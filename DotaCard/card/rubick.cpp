#include "rubick.h"

Rubick::Rubick()
{
    ISDN = 606;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Dark_Attribute;
    type = Card::Spellcaster_Type;
    level = 4;
    ATK = 900;
    DEF = 300;
    name = "Rubick";
    description = tr("Rubick");

    currentATK = ATK;
    currentDEF = DEF;
}
