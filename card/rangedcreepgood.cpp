#include "rangedcreepgood.h"

RangedCreepGood::RangedCreepGood()
{
    ISDN = 3;
    name = "rangedcreepgood";
    description = tr("rangedcreepgood"); //远程兵（天辉）
    attribute = Light_Attribute;
    level = 3;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 1200;
    DEF = 1300;
}
