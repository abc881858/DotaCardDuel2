#include "siegecreepbad.h"

SiegeCreepBad::SiegeCreepBad()
{
    ISDN = 6;
    name = "siegecreepbad";
    description = tr("siegecreepbad"); //攻城车（夜魇）
    attribute = Dark_Attribute;
    level = 4;
    kind = NormalMonster_Kind;
    type = Machine_Type;
    ATK = 500;
    DEF = 2000;
}
