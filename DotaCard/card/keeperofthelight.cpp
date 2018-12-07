#include "keeperofthelight.h"

KeeperoftheLight::KeeperoftheLight()
{
    ISDN = 602;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Light_Attribute;
    type = Card::Spellcaster_Type;
    level = 3;
    ATK = 800;
    DEF = 300;
    name = "KeeperoftheLight";
    description = tr("KeeperoftheLight");

    currentATK = ATK;
    currentDEF = DEF;
}
