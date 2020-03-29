#include "effectmonster.h"

EffectMonster::EffectMonster()
{

}

bool EffectMonster::testActive()
{
    if(!Card::testActive())
    {
        return false;
    }
    if(isForbidden)//是否被禁止怪兽效果
    {
        return false;
    }
    return true;
}
