#include "nyxassassin.h"

NyxAssassin::NyxAssassin()
{
    ISDN = 605;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Dark_Attribute;
    type = Card::Insect_Type;
    level = 4;
    ATK = 1500;
    DEF = 800;
    name = "NyxAssassin";
    description = tr("NyxAssassin");

    currentATK = ATK;
    currentDEF = DEF;
}
