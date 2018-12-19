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
    EffectMonsterCard::standby();

    //准备阶段自动做的事, 每回合一次在这初始化
    canEffect1 = true;
    canEffect2 = true;
}

bool CentaurWarrunner::testEffectFromFieldyard()
{
    if(!qDota->whoIsDoing)
    {
        return false;
    }
    if(area != Card::Fieldyard_Area)
    {
        return false;
    }

    if (qDota->phase == Dota::EnemyBattle_Phase) //在对方战斗流程连锁
    {
        if(canEffect1)
        {
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
            return true;
        }
    }
    return false;
}

void CentaurWarrunner::active()
{
    qDebug() << "active CentaurWarrunner";
    int effectNum = QMessageBox::question(nullptr, QString(tr("selecting")), QString(tr("Active Which Effect")), "CentaurWarrunner_1", "CentaurWarrunner_2");
    switch(effectNum)
    {
    case 0:
        //将这张卡作为祭品发动，强制结束对方的战斗阶段。
        //若这张卡装备了“dota-跳刀”，
        //则可以改为丢弃一张手牌发动
        qDebug() << "CentaurWarrunner_1";
        break;
    case 1:
        //你的每回合一次，在对方场合也可以发动
        /* 你可以让自己场上名字带有“dota”的怪兽全部变为攻击表示或防守表示，
        * 若这张卡装备了“dota-阿哈利姆神杖”时，
        * 同时令自己场上名字带有“dota”的怪兽的攻击力（或防御力）上升自己
        * 原本攻击力（或防御力）的一半。*/
        qDebug() << "CentaurWarrunner_2";
        break;
    }
}
