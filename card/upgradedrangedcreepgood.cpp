#include "upgradedrangedcreepgood.h"

UpgradedRangedCreepGood::UpgradedRangedCreepGood()
{
    ISDN = 9;
    name = "upgradedrangedcreepgood";
    description = tr("upgradedrangedcreepgood"); //高级远程兵（天辉）
    attribute = Light_Attribute;
    level = 5;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 2200;
    DEF = 2300;
}
