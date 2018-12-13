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

void UrnOfShadows::afterEquip()
{
    equipMonsterCard->setCurrentDEF(equipMonsterCard->getCurrentDEF()+100);
    qDota->resetAtkDef(equipMonsterCard);
}
