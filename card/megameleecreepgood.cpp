#include "megameleecreepgood.h"

MegaMeleeCreepGood::MegaMeleeCreepGood()
{
    ISDN = 13;
    name = "megameleecreepgood";
    description = tr("megameleecreepgood"); //超级近程兵（天辉）
    attribute = Light_Attribute;
    level = 7;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 3300;
    DEF = 3200;
}
