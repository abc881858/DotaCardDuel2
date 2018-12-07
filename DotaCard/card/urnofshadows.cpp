#include "urnofshadows.h"
#include "dota.h"
#include <QMessageBox>
#include <QDebug>

UrnOfShadows::UrnOfShadows()
{
    ISDN = 704;
    name = "UrnOfShadows";
    description = tr("UrnOfShadows");
}

void UrnOfShadows::standby()
{
    EquipSpellCard::standby();
}
