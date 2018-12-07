#include "card.h"
#include "dota.h"

Card::Card()
{
    area = No_Area;
    stand = true;
    face = false;
    enemy = false;

    ISDN = -1;
    kind = Card::No_Kind;
    attribute = Card::No_Attribute;
    type = Card::No_Type;
    level = 0;
    ATK = -1;
    DEF = -1;
    name = "no_name";
    description = "no_description";

    currentATK = -1;
    currentDEF = -1;
    equipMonsterCard = nullptr;
    count_turn = 0;

    canAttack = false;

}

void Card::standby()
{
}

bool Card::testEffectFromHand()
{
    if(area != Card::Hand_Area)
    {
        return false;
    }
    return false;
}

bool Card::testSpecialSummon()
{
    if(area != Card::Hand_Area)
    {
        return false;
    }
    return false;
}

bool Card::testNormalSummon()
{
    return false;
}

bool Card::testSetCard()
{
    return false;
}

bool Card::testEffectFromFieldyard()
{
    return false;
}

bool Card::testDefencePosition()
{
    if(area != Card::Fieldyard_Area)
    {
        return false;
    }
    return false;
}

bool Card::testAttackPosition()
{
    if(area != Card::Fieldyard_Area)
    {
        return false;
    }
    return false;
}

bool Card::testFlipSummon()
{
    return false;
}

bool Card::testAttack()
{
    return false;
}

bool Card::testEffectFromFieldground()
{
    return false;
}

int Card::getISDN() const
{
    return ISDN;
}

Card::KindFlag Card::getKind() const
{
    return kind;
}

void Card::setupCard()
{
    area = Card::Deck_Area;
    stand = true;
    face = false;
    enemy = false;
}

void Card::enemySetupCard()
{
    area = Card::EnemyDeck_Area;
    stand = true;
    face = false;
    enemy = true;
}

void Card::drawCard()
{
    area = Card::Hand_Area;
    stand = true;
    face = true;
    enemy = false;
}

void Card::enemyDrawCard()
{
    area = Card::EnemyHand_Area;
    stand = true;
    face = false;
    enemy = true;
}

void Card::specialSummonCard()
{
    area = Card::Fieldyard_Area;
    stand = true;
    face = true;
    enemy = false;
}

void Card::enemySpecialSummonCard()
{
    area = Card::EnemyFieldyard_Area;
    stand = true;
    face = true;
    enemy = true;
}

void Card::summonCard()
{
    qDota->oneTurnOneNormalSummon = false;
    area = Card::Fieldyard_Area;
    stand = true;
    face = true;
    enemy = false;
}

void Card::enemySummonCard()
{
    area = Card::EnemyFieldyard_Area;
    stand = true;
    face = true;
    enemy = true;
}

void Card::activeCard()
{
    area = Card::Fieldground_Area;
    stand = true;
    face = true;
    enemy = false;
}

void Card::active()
{

}

int Card::getATK() const
{
    return ATK;
}

void Card::setATK(int value)
{
    ATK = value;
}

void Card::enemyActiveCard()
{
    area = Card::EnemyFieldground_Area;
    stand = true;
    face = true;
    enemy = true;
}

void Card::setCard()
{
    qDota->oneTurnOneNormalSummon = false;
    area = Card::Fieldyard_Area;
    stand = false;
    face = false;
    enemy = false;
}

void Card::enemySetCard()
{
    area = Card::EnemyFieldyard_Area;
    stand = false;
    face = false;
    enemy = true;
}

void Card::destroyCard()
{
    area = Card::Graveyard_Area;
    stand = true;
    face = true;
    enemy = false;
}

void Card::enemyDestroyCard()
{
    area = Card::EnemyGraveyard_Area;
    stand = true;
    face = true;
    enemy = true;
}

void Card::setArea(const AreaFlag &value)
{
    area = value;
}

void Card::setStand(bool value)
{
    stand = value;
}

Card::AreaFlag Card::getArea() const
{
    return area;
}

bool Card::getFace() const
{
    return face;
}

bool Card::getStand() const
{
    return stand;
}
