#include "effectmonstercard.h"
#include "dota.h"

EffectMonsterCard::EffectMonsterCard()
{

}

bool EffectMonsterCard::testNormalSummon()
{
    if(qDota->phase == Dota::Main1_Phase
        || qDota->phase == Dota::Main2_Phase)
    {
        if(qDota->oneTurnOneNormalSummon)
        {
            if(area == Card::Hand_Area)
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

bool EffectMonsterCard::testAttack()
{
    if(area == Card::Fieldyard_Area)
    {
        if(qDota->phase == Dota::Battle_Phase)
        {
            if(stand && face && oneTurnOneAttack)
            {
                return true;
            }
        }
    }
    return false;
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
    oneTurnOneAttack = true;
}
