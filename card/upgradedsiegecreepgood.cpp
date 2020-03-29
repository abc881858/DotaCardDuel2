#include "upgradedsiegecreepgood.h"

UpgradedSiegeCreepGood::UpgradedSiegeCreepGood()
{
    ISDN = 11;
    name = "upgradedsiegecreepgood";
    description = tr("upgradedsiegecreepgood"); //高级攻城车（天辉）
    attribute = Light_Attribute;
    level = 6;
    kind = NormalMonster_Kind;
    type = Machine_Type;
    ATK = 1500;
    DEF = 3000;
}
