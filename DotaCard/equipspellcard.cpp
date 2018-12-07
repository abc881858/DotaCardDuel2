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

bool EquipSpellCard::testEffectFromFieldground()
{
    return false;
}

void EquipSpellCard::standby()
{
    //准备阶段自动做的事, 每回合一次在这初始化
    oneTurnEffect3 = true;
}

void EquipSpellCard::active()
{

}
