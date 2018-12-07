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
