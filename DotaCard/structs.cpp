#include "structs.h"

CardMoveStruct::CardMoveStruct()
{
    areaFrom = Card::No_Area;
    areaTo = Card::No_Area;
    indexFrom = -1;
    indexTo = -1;
    reason = REASON_unknown;
}

QJsonObject CardMoveStruct::toJson() const
{
    QJsonObject json;
    switch (areaFrom)
    {
    case Card::EnemyDeck_Area:
        json.insert("areaFrom", 1);
        break;
    case Card::EnemyHand_Area:
        json.insert("areaFrom", 2);
        break;
    case Card::EnemyFieldyard_Area:
        json.insert("areaFrom", 3);
        break;
    case Card::EnemyFieldground_Area:
        json.insert("areaFrom", 4);
        break;
    case Card::EnemyGraveyard_Area:
        json.insert("areaFrom", 5);
        break;
    case Card::Deck_Area:
        json.insert("areaFrom", 6);
        break;
    case Card::Hand_Area:
        json.insert("areaFrom", 7);
        break;
    case Card::Fieldyard_Area:
        json.insert("areaFrom", 8);
        break;
    case Card::Fieldground_Area:
        json.insert("areaFrom", 9);
        break;
    case Card::Graveyard_Area:
        json.insert("areaFrom", 10);
        break;
    default:
        break;
    }
    switch (areaTo)
    {
    case Card::EnemyDeck_Area:
        json.insert("areaTo", 1);
        break;
    case Card::EnemyHand_Area:
        json.insert("areaTo", 2);
        break;
    case Card::EnemyFieldyard_Area:
        json.insert("areaTo", 3);
        break;
    case Card::EnemyFieldground_Area:
        json.insert("areaTo", 4);
        break;
    case Card::EnemyGraveyard_Area:
        json.insert("areaTo", 5);
        break;
    case Card::Deck_Area:
        json.insert("areaTo", 6);
        break;
    case Card::Hand_Area:
        json.insert("areaTo", 7);
        break;
    case Card::Fieldyard_Area:
        json.insert("areaTo", 8);
        break;
    case Card::Fieldground_Area:
        json.insert("areaTo", 9);
        break;
    case Card::Graveyard_Area:
        json.insert("areaTo", 10);
        break;
    default:
        break;
    }

    json.insert("indexFrom", indexFrom);
    json.insert("indexTo", indexTo);
    json.insert("reason", -reason);

    return json;
}

CardMoveStruct CardMoveStruct::fromJson(QJsonObject json)
{
    CardMoveStruct move;
    move.areaFrom =  Card::AreaFlag(json["areaFrom"].toInt());
    move.areaTo = Card::AreaFlag(json["areaTo"].toInt());
    move.indexFrom = json["indexFrom"].toInt();
    move.indexTo = json["indexTo"].toInt();
    move.reason = json["reason"].toInt();

    return move;
}
