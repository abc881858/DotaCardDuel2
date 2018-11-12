#include "equipspellcard.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

EquipSpellCard::EquipSpellCard()
{
    kind = Card::EquipSpell_Kind;

    oneTurnEffect3 = true;
}

bool EquipSpellCard::testEffectFromHand()
{
    if(area != Card::Hand_Area)
    {
        return false;
    }
    if(qDota->phase != Dota::Main1_Phase && qDota->phase != Dota::Main2_Phase)
    {
        return false;
    }
    if(!qDota->hasEmptyBackSlot())
    {
        return false;
    }
    if(!qDota->hasMonster())
    {
        return false;
    }
    //如果没有其他不允许发动魔法卡之说
    return true;
}

int EquipSpellCard::testEffectFromFieldyard()
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
        if (oneTurnEffect3) //一回合一次
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

void EquipSpellCard::standby()
{
    //准备阶段自动做的事, 每回合一次在这初始化
    oneTurnEffect3 = true;
}

void EquipSpellCard::active()
{
    //先到场地，发光，弹出对话框，点确定，选择卡，装备卡动画
    if(QMessageBox::information(nullptr, "title", "please select one monster to equip.", QMessageBox::Yes))
    {
        qDebug() << "selectOneMonsterToEquip";
    }
    qDota->setSearchReason(Dota::BeEquiped_Reason);
}
