#include "engine.h"
#include "megameleecreepbad.h"
#include "megameleecreepgood.h"
#include "megarangedcreepbad.h"
#include "megarangedcreepgood.h"
#include "meleecreepbad.h"
#include "meleecreepgood.h"
#include "rangedcreepbad.h"
#include "rangedcreepgood.h"
#include "siegecreepbad.h"
#include "siegecreepgood.h"
#include "upgradedmeleecreepbad.h"
#include "upgradedmeleecreepgood.h"
#include "upgradedrangedcreepbad.h"
#include "upgradedrangedcreepgood.h"
#include "upgradedsiegecreepbad.h"
#include "upgradedsiegecreepgood.h"
#include "pugna.h"

Q_GLOBAL_STATIC(Engine, engine)

Engine* Engine::instance()
{
    return engine();
}

void Engine::initialize()
{
    allclass << new MegaMeleeCreepBad()
             << new MegaMeleeCreepGood()
             << new MegaRangedCreepBad()
             << new MegaRangedCreepGood()
             << new MeleeCreepBad()
             << new MeleeCreepGood()
             << new RangedCreepBad()
             << new RangedCreepGood()
             << new SiegeCreepBad()
             << new SiegeCreepGood()
             << new UpgradedMeleeCreepBad()
             << new UpgradedMeleeCreepGood()
             << new UpgradedRangedCreepBad()
             << new UpgradedRangedCreepGood()
             << new UpgradedSiegeCreepBad()
             << new UpgradedSiegeCreepGood()
             << new Pugna();

    for (Card* card : allclass)
    {
        metaobjects.insert(card->getISDN(), card->metaObject());
    }
}

Card* Engine::cloneCard(int ISDN)
{
    const QMetaObject* meta = metaobjects.value(ISDN);
    if(meta == nullptr)
    {
        return nullptr;
    }
    return qobject_cast<Card*>(meta->newInstance());
}
