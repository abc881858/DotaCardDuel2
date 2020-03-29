#include "siegecreepgood.h"

SiegeCreepGood::SiegeCreepGood()
{
    ISDN = 5;
    name = "siegecreepgood";
    description = tr("siegecreepgood"); //攻城车（天辉）
    attribute = Light_Attribute;
    level = 4;
    kind = NormalMonster_Kind;
    type = Machine_Type;
    ATK = 500;
    DEF = 2000;
}
