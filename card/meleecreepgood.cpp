#include "meleecreepgood.h"

MeleeCreepGood::MeleeCreepGood()
{
    ISDN = 1;
    name = "meleecreepgood";
    description = tr("meleecreepgood"); //近程兵（天辉）
    attribute = Light_Attribute;
    level = 3;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 1300;
    DEF = 1200;
}
