#include "gemoftruesight.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

GemOfTrueSight::GemOfTrueSight()
{
    ISDN = 703;
    name = "GemOfTrueSight";
    description = tr("GemOfTrueSight");
}

void GemOfTrueSight::standby()
{
    EquipSpellCard::standby();
}

void GemOfTrueSight::active()
{
    qDebug() << "active GemOfTrueSight";
}

void GemOfTrueSight::destroyByEquipMonster()
{
    CardMoveStruct move;
    move.areaFrom = Card::Fieldground_Area;
    move.areaTo = Card::EnemyHand_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = -1;
    move.reason = CardMoveStruct::REASON_destroyByEquipMonster;

    enemyDrawCard();

    qDota->moveCard(move);
}

void GemOfTrueSight::destroyByEnemyEquipMonster()
{
    CardMoveStruct move;
    move.areaFrom = Card::EnemyFieldground_Area;
    move.areaTo = Card::Hand_Area;
    move.indexFrom = qDota->getCardIndex(this);
    move.indexTo = -1;
    move.reason = CardMoveStruct::REASON_destroyByEnemyEquipMonster;

    drawCard();

    qDota->moveCard(move);
}
