#include "centaurwarrunner.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

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

    canEffect1 = true;
    canEffect2 = true;
}

void CentaurWarrunner::standby()
{
    //先调用基类的standby函数，初始化一些变量，例如 oneTurnOneAttack
    Card::standby();

    //准备阶段自动做的事, 每回合一次在这初始化
    canEffect1 = true;
    canEffect2 = true;
}

bool CentaurWarrunner::testEffectFromFieldyard()
{
    if(area != Card::Fieldyard_Area)
    {
        return false;
    }

    if (qDota->phase == Dota::EnemyBattle_Phase) //在对方战斗流程连锁
    {
        if(canEffect1)
        {
//            canEffect1 = false;
            return true;
        }
    }
    if (qDota->phase == Dota::Main1_Phase ||
            qDota->phase == Dota::Main2_Phase ||
            qDota->phase == Dota::EnemyMain1_Phase ||
            qDota->phase == Dota::EnemyBattle_Phase ||
            qDota->phase == Dota::EnemyMain2_Phase)
    {
        if (canEffect2) //一回合一次
        {
//            canEffect2 = false;
            return true;
        }
    }
    return false;
}

void CentaurWarrunner::active()
{
    qDebug() << "active CentaurWarrunner";
}
