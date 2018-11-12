#include "centaurwarrunner.h"
#include "dota.h"
#include <QMessageBox>

CentaurWarrunner::CentaurWarrunner()
{
    ISDN = 601;
    kind = Card::EffectMonster_Kind;
    attribute = Card::Earth_Attribute;
    type = Card::Warrior_Type;
    level = 3;
    ATK = 1350;
    DEF = 1800;
    name = "CentaurWarrunner";
    description = tr("CentaurWarrunner");

    currentATK = ATK;
    currentDEF = DEF;

    oneTurnEffect2 = true;
}

void CentaurWarrunner::standby()
{
    //先调用基类的standby函数，初始化一些变量，例如 oneTurnOneAttack
    Card::standby();

    //准备阶段自动做的事, 每回合一次在这初始化
    oneTurnEffect2 = true;
}

int CentaurWarrunner::testEffectFromFieldyard()
{
    if(area != Card::Fieldyard_Area)
    {
        return 0;
    }

    int result = 0;
    if (qDota->phase == Dota::EnemyBattle_Phase) //在对方战斗流程连锁
    {
//        qDota->whoIsDoing 能进 test 的流程，说明一定是 我在行动
        result += 1;
    }
    if (qDota->phase == Dota::Main1_Phase ||
            qDota->phase == Dota::Main2_Phase ||
            qDota->phase == Dota::EnemyMain1_Phase ||
            qDota->phase == Dota::EnemyBattle_Phase ||
            qDota->phase == Dota::EnemyMain2_Phase)
    {
        if (oneTurnEffect2) //一回合一次
        {
            //一般是M1、M2的request可能为Positive，对方的M1、BP、M2可能为Negative
            if (area == Card::Fieldyard_Area)
            {
                result += 2;
            }
        }
    }
    return result;
}
