#include "equipspellcard.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

EquipSpellCard::EquipSpellCard()
{
    kind = Card::EquipSpell_Kind;
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
}

void EquipSpellCard::beforeEquip()
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldground_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = qDota->testPlace(Card::Fieldground_Area);
    move.reason = CardMoveStruct::REASON_activeSpellCard;

    Card::beforeEquip();

    qDota->moveCard(move);

    qDota->whoIsDoing = false;

    emit qDota->showChainAnimation(move.indexTo, Card::Fieldground_Area);
//    qNet->sendChained(move.indexTo, Card::Fieldground_Area); // 考虑下提前发送Net连锁动画

}

void EquipSpellCard::destroyByEquipMonster()
{
    CardMoveStruct move;
    move.areaFrom = Card::Fieldground_Area;
    move.areaTo = Card::Graveyard_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = -1;
    move.reason = CardMoveStruct::REASON_destroyCard;

    destroyCard();

    qDota->moveCard(move);
}

void EquipSpellCard::destroyByEnemyEquipMonster()
{
    CardMoveStruct move;
    move.areaFrom = Card::EnemyFieldground_Area;
    move.areaTo = Card::EnemyGraveyard_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = -1;
    move.reason = CardMoveStruct::REASON_destroyEnemyCard;

    enemyDestroyCard();

    qDota->moveCard(move);
}
