#include "rangedcreepbad.h"

RangedCreepBad::RangedCreepBad()
{
    ISDN = 4;
    name = "rangedcreepbad";
    description = tr("rangedcreepbad"); //远程兵（夜魇）
    attribute = Dark_Attribute;
    level = 3;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 1200;
    DEF = 1300;
}
