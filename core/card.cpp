#include "card.h"
#include "game.h"

Card::Card()
{
}

bool Card::testActive() //测试能否主动发动
{
    if(!qGame->isMyturn)//是否我的回合
    {
        return false;
    }
    if(!qGame->isMyMain)//是否我的主要流程
    {
        return false;
    }
    if(!qGame->isMyAct)//是否我的行动
    {
        return false;
    }
    return true;
}
