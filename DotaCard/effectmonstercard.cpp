#include "effectmonstercard.h"
#include "dota.h"
#include <QDebug>

EffectMonsterCard::EffectMonsterCard()
{
    canAttack = false;
}

bool EffectMonsterCard::testNormalSummon()
{
    if(area != Card::Hand_Area)
    {
        return false;
    }

    if(qDota->testPlace(Card::Fieldyard_Area) == -1) // 整理下，以后会提示前排已满
    {
        return false;
    }

    if(qDota->phase == Dota::Main1_Phase
        || qDota->phase == Dota::Main2_Phase)
    {
        if(qDota->oneTurnOneNormalSummon)
        {
            if(level>0 && level<5)
            {
                return true;
            }
            //TODO: 5星以上需要祭品
        }
    }
    return false;
}

bool EffectMonsterCard::testAttack()
{
    if(area == Card::Fieldyard_Area)
    {
        if(qDota->phase == Dota::Battle_Phase)
        {
            if(stand && face)
            {
                return true;
            }
        }
    }
    return false;
}

bool EffectMonsterCard::testEffectFromFieldyard()
{
    return false;
}

void EffectMonsterCard::specialSummonCard()
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = qDota->testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_specialSummonCard;

    area = Card::Fieldyard_Area;
    stand = true;
    face = true;
    enemy = false;

    qDota->moveCard(move);
}

void EffectMonsterCard::summonCard()
{
    qDota->oneTurnOneNormalSummon = false;

    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = qDota->testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_summonCard;

    area = Card::Fieldyard_Area;
    stand = true;
    face = true;
    enemy = false;

    qDota->moveCard(move);
}

void EffectMonsterCard::setCard()
{
    qDota->oneTurnOneNormalSummon = false;

    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = qDota->testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_setCard;

    area = Card::Fieldyard_Area;
    stand = false;
    face = false;
    enemy = false;

    qDota->moveCard(move);
}

bool EffectMonsterCard::testSetCard()
{
    if(qDota->phase == Dota::Main1_Phase
        || qDota->phase == Dota::Main2_Phase)
    {
        if(qDota->oneTurnOneNormalSummon)
        {
            if (area == Card::Hand_Area)
            {
                if(level>0 && level<5)
                {
                    return true;
                }
                //TODO: 5星以上需要祭品
            }
        }
    }
    return false;
}

bool EffectMonsterCard::testFlipSummon()
{
    if(area != Card::Fieldyard_Area)
    {
        return false;
    }
    return false;
}

void EffectMonsterCard::standby()
{
    Card::standby();
    canAttack = true;
}
