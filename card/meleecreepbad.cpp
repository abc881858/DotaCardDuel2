#include "meleecreepbad.h"

MeleeCreepBad::MeleeCreepBad()
{
    ISDN = 2;
    name = "meleecreepbad";
    description = tr("meleecreepbad"); //近战兵（夜魇）
    attribute = Dark_Attribute;
    level = 3;
    kind = NormalMonster_Kind;
    type = Warrior_Type;
    ATK = 1300;
    DEF = 1200;
}
