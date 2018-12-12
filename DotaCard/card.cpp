﻿#include "card.h"
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

QString Card::getFieldPath()
{
    return QString(":/field/%1").arg(name);
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

void Card::beforeActive()
{
    area = Card::Fieldground_Area;
    stand = true;
    face = true;
    enemy = false;
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

void Card::enemySpecialSummonCard()
{
    area = Card::EnemyFieldyard_Area;
    stand = true;
    face = true;
    enemy = true;
}

void Card::enemySummonCard()
{
    area = Card::EnemyFieldyard_Area;
    stand = true;
    face = true;
    enemy = true;
}

int Card::getCurrentATK() const
{
    return currentATK;
}

void Card::setCurrentATK(int value)
{
    currentATK = value;
}

int Card::getCurrentDEF() const
{
    return currentDEF;
}

void Card::setCurrentDEF(int value)
{
    currentDEF = value;
}

void Card::setFace(bool value)
{
    face = value;
}

void Card::setEnemy(bool value)
{
    enemy = value;
}

int Card::getLevel() const
{
    return level;
}

void Card::enemyActiveSpellCard()
{
    area = Card::EnemyFieldground_Area;
    stand = true;
    face = true;
    enemy = true;
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
