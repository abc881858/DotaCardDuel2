#include "forcestaff.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

ForceStaff::ForceStaff()
{
    ISDN = 702;
    name = "ForceStaff";
    description = tr("ForceStaff");
    canEffect = true;
}

void ForceStaff::standby()
{
    EquipSpellCard::standby();
    canEffect = true;
}

bool ForceStaff::testEffectFromFieldground()
{
    if(canEffect)
    {
//        canEffect = false;
        return true;
    }
    return false;
}

void ForceStaff::active()
{
    qDebug() << "active ForceStaff";
}
