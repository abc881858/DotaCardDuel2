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

void ForceStaff::active()
{
    int effectNum = QMessageBox::question(nullptr, QString(tr("selecting")), QString(tr("Active Which Effect")), "ForceStaff_1", "ForceStaff_2", "ForceStaff_3");
    switch(effectNum)
    {
    case 0:
        //不受对方 AOE 影响
        qDebug() << "active ForceStaff_1";
        break;
    case 1:
        //当对方攻击破坏我方一只怪兽，我方怪兽不送入墓地，然后该效果失去
        qDebug() << "active ForceStaff_2";
        break;
    case 2:
        //我方攻击对方被无效时，我方该怪兽再进行一次攻击，然后该效果失去
        qDebug() << "active ForceStaff_3";
        break;
    }
    canEffect = false;
}
