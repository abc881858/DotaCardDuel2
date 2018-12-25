#ifndef STRUCTS_H
#define STRUCTS_H

#include <QVariant>
#include "card.h"
#include <QJsonObject>

class CardMoveStruct
{
public:
    Card::AreaFlag areaFrom;
    Card::AreaFlag areaTo;
    int indexFrom;
    int indexTo;
    int reason;

    static const int REASON_unknown = 0;
    static const int REASON_drawCard = 2;
    static const int REASON_enemyDrawCard = -2;
    static const int REASON_specialSummonCard = 3;
    static const int REASON_enemySpecialSummonCard = -3;
    static const int REASON_summonCard = 4;
    static const int REASON_enemySummonCard = -4;
    static const int REASON_activeSpellCard = 5;
    static const int REASON_enemyActiveSpellCard = -5;
    static const int REASON_setCard = 6;
    static const int REASON_enemySetCard = -6;
    static const int REASON_destroyCard = 7;
    static const int REASON_enemyDestroyCard = -7;
    static const int REASON_destroyEnemyCard = 8;
    static const int REASON_enemyDestroyEnemyCard = -8;
    static const int REASON_specialSummonDeckCard = 9;
    static const int REASON_enemyspecialSummonDeckCard = -9;
    static const int REASON_destroyByEquipMonster = 10;
    static const int REASON_destroyByEnemyEquipMonster = 11;
    static const int REASON_enemyDestroyByEquipMonster = -10;
    static const int REASON_enemyDestroyByEnemyEquipMonster = -11;

    CardMoveStruct();

    QJsonObject toJson() const;
    static CardMoveStruct fromJson(QJsonObject json);
};
Q_DECLARE_METATYPE(CardMoveStruct)

class AtkDefChangeStruct
{
public:
    Card::AreaFlag area;
    int index;
    int atk;
    int def;

    AtkDefChangeStruct();
};
Q_DECLARE_METATYPE(AtkDefChangeStruct)

#endif // STRUCTS_H
