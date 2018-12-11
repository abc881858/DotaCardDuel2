#include "satanic.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

Satanic::Satanic()
{
    ISDN = 705;
    name = "Satanic";
    description = tr("Satanic");
    canEffect = true;
}

void Satanic::standby()
{
    EquipSpellCard::standby();
    canEffect = true;
}

void Satanic::beforeActive()
{

}

bool Satanic::testEffectFromFieldground()
{
    if(area != Card::Fieldground_Area)
    {
        return false;
    }

    if (qDota->phase == Dota::Main1_Phase ||
            qDota->phase == Dota::Main2_Phase)
    {
        if(canEffect)
        {
            return true;
        }
    }
    return false;
}
