#include "megarangedcreepgood.h"

MegaRangedCreepGood::MegaRangedCreepGood()
{
    ISDN = 15;
    name = "megarangedcreepgood";
    description = tr("megarangedcreepgood"); //超级远程兵（天辉）
    attribute = Light_Attribute;
    level = 7;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 3200;
    DEF = 3300;
}
