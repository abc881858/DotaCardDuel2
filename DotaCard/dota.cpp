#include "dota.h"

Q_GLOBAL_STATIC(Dota, dota)

Dota* Dota::instance()
{
    return dota();
}

void Dota::initialize()
{
    phase = No_Phase;
    whoIsDoing = true;

    oneTurnOneNormalSummon = false;
    firstTurn = true;

    attackSourceCard = nullptr;

    authenticateCardAreaList.clear(); //初始化鉴权
    authenticateCardActive = false;

    for(int i = 0; i < 5; ++i)
    {
        fieldyardCards[i] = nullptr;
        fieldgroundCards[i] = nullptr;
        enemyFieldyardCards[i] = nullptr;
        enemyFieldgroundCards[i] = nullptr;
    }

    room = new Room;
}

void Dota::setSearchReason(Dota::ReasonFlag flag)
{
    searchReason = flag;

    if(flag == Dota::No_Reason)
    {
        authenticateCardAreaList.clear();
        authenticateCardActive = false; //不再寻找攻击目标
    }
    else if(flag==Dota::BeAttacked_Reason)
    {
        addAuthenticateCardArea(Card::EnemyFieldyard_Area);
    }
    else if(flag==Dota::ChainDeclared_Reason)
    {
        addAuthenticateCardArea(Card::Fieldyard_Area);
        addAuthenticateCardArea(Card::Fieldground_Area);
        needAuthenticateCardActive();
    }
    else if(flag==Dota::BeEquiped_Reason)
    {
        addAuthenticateCardArea(Card::Fieldyard_Area);
    }
}

Dota::ReasonFlag Dota::getSearchReason()
{
    return searchReason;
}

bool Dota::isSearchingTargetCard()
{
    if(!authenticateCardAreaList.isEmpty())
    {
        return true;
    }
//    一般 target 都有 area，可以以小见大,窥一斑而知全豹
//    if(authenticateCardActive)
//    {
//        return true;
//    }
    return false; //全部 authenticate 都不 need
}

void Dota::addAuthenticateCardArea(Card::AreaFlag flag)
{
    authenticateCardAreaList << flag;
}

void Dota::needAuthenticateCardActive()
{
    authenticateCardActive = true;
}

bool Dota::authenticateCard(Card *card)
{
    if(!authenticateCardAreaList.isEmpty())
    {
        if(!authenticateCardAreaList.contains(card->getArea()))
        {
            return false;
        }
    }
    if(authenticateCardActive)
    {
        if(card->getArea() == Card::Fieldyard_Area)
        {
            if(card->testEffectFromFieldyard() == 0)
            {
                return false;
            }
        }
        else if(card->getArea() == Card::Fieldground_Area)
        {
            if(!card->testEffectFromFieldground())
            {
                return false;
            }
        }
    }
    return true; //全部都鉴权成功，return true
}

int Dota::getCardIndexOfFieldyard(Card* card)
{
    if(card != nullptr)
    {
        for (int i = 0; i < 5; ++i)
        {
            if(fieldyardCards[i] == card)
            {
                return i;
            }
        }
    }
    return -1;
}

int Dota::getCardIndexOfEnemyFieldyard(Card *card) //专属攻击，不用遍历场上全部卡牌
{
    if(card != nullptr)
    {
        for (int i = 0; i < 5; ++i)
        {
            if(enemyFieldyardCards[i] == card)
            {
                return i;
            }
        }
    }
    return -1;
}

int Dota::getCardIndexOfFieldground(Card* card)
{
    if(card != nullptr)
    {
        for (int i = 0; i < 5; ++i)
        {
            if(fieldgroundCards[i] == card)
            {
                return i;
            }
        }
    }
    return -1;
}

int Dota::getCardIndexOfEnemyFieldground(Card *card)
{
    if(card != nullptr)
    {
        for (int i = 0; i < 5; ++i)
        {
            if(enemyFieldgroundCards[i] == card)
            {
                return i;
            }
        }
    }
    return -1;
}

int Dota::getCardIndexOfArea(Card* card, Card::AreaFlag flag)
{
    if(flag == Card::Fieldyard_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(fieldyardCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::EnemyFieldyard_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(enemyFieldyardCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::Fieldground_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(fieldgroundCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::EnemyFieldground_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(enemyFieldgroundCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

//////////////////////
bool Dota::hasMonster()
{
    for(int i=0; i<5; i++)
    {
        if(fieldyardCards[i] != nullptr)
        {
            return true;
        }
    }
    return false;
}

bool Dota::hasEnemyMonster()
{
    for(int i=0; i<5; i++)
    {
        if(enemyFieldyardCards[i] != nullptr)
        {
            return true;
        }
    }
    return false;
}

//Card* Dota::getEffectCard()
//{
//    return nullptr;
//}

//Card* Dota::getSelectCard()
//{
//    return nullptr;
//}

//void Dota::changeLp(bool isMine)
//{
//    Q_UNUSED(isMine)
//}

//bool Dota::canActiveSpell()
//{
//    return false;
//}

bool Dota::hasEmptyBackSlot()
{
    for(int i=0; i<5; i++)
    {
        if(fieldgroundCards[i] == nullptr)
        {
            return true;
        }
    }
    return false;
}

bool Dota::hasEmptyFrontSlot()
{
    for(int i=0; i<5; i++)
    {
        if(fieldyardCards[i] == nullptr)
        {
            return true;
        }
    }
    return false;
}
