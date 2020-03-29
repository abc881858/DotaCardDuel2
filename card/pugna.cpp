#include "pugna.h"
#include <QDebug>
#include "game.h"

Pugna::Pugna()
{
    ISDN = 17;
    name = "pugna";
    description = tr("pugna"); //帕格纳
    attribute = Dark_Attribute;
    level = 3;
    kind = EffectMonster_Kind;
    type = Zombie_Type;
    ATK = 1200;
    DEF = 100;

    activeList << new ActiveEffect{"pugna_effect1",true,false};

//    passiveList << PassiveEffect{"pugna_effect2"};
}

bool Pugna::testActive()
{
    if(!EffectMonster::testActive())
    {
        return false;
    }

    for(ActiveEffect *effect : activeList)
    {
        if(effect->isOnce)
        {
            if(!effect->hasActived)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

//主动技能
void Pugna::active()
{
    //是否需要丢弃手牌或者除外卡牌等COST
    //是否需要选定目标发动

    QList<QString> effectNames;//可以发动效果的全部效果名称

    for(ActiveEffect *effect : activeList)
    {
        if(effect->isOnce)
        {
            if(!effect->hasActived)
            {
                effectNames << effect->name;
            }
        }
        else
        {
            effectNames << effect->name;
        }
    }

    if(effectNames.size() == 1)
    {
        QString effectName = effectNames.first();
        qGame->askWhetherActive(effectName);
    }
    else if(effectNames.size() > 1)//是否有多项技能可发动
    {
        qGame->askWhichActive(effectNames);
    }
    else
    {
        //不可能
        qDebug() << "effectNames size == 0";
    }
}

//被动技能
void Pugna::passive()
{
    //decrease remote LP
}

//效果1：一回合一次，指定对方场上一只怪兽或我方场上一只怪兽发动，指定的怪兽在你下回合开始前不能攻击，但也不会成为攻击对象
//效果2：只要这张卡在场上表侧表示，对方发动魔法卡时将受到1000点LP伤害

//主动发动技能，hover时需要检测是否能发动
//常见的，Card子类需要UI配合，去指定一张CardItem
//被动发动技能，由某一种UI事件触发
