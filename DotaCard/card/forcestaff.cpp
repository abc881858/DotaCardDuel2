#include "forcestaff.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

ForceStaff::ForceStaff()
{
    ISDN = 702;
    name = "ForceStaff";
    description = tr("ForceStaff");
}

void ForceStaff::standby()
{
    EquipSpellCard::standby();
}

void ForceStaff::active()
{
    EquipSpellCard::active();
}
