#include "engine.h"
#include "card/centaurwarrunner.h"
#include "card/keeperofthelight.h"
#include "card/lion.h"
#include "card/magnus.h"
#include "card/nyxassassin.h"
#include "card/rubick.h"
#include "card/tusk.h"
#include "card/undying.h"
#include "card/vengefulspirit.h"
#include "card/zeus.h"

#include "card/forcestaff.h"
#include "card/gemoftruesight.h"
#include "card/helmofthedominator.h"
#include "card/urnofshadows.h"

Q_GLOBAL_STATIC(Engine, engine)

Engine* Engine::instance()
{
    return engine();
}

void Engine::loadAllClass()
{
    allclass << new CentaurWarrunner()
             << new KeeperoftheLight()
             << new Lion()
             << new Magnus()
             << new NyxAssassin()
             << new Rubick()
             << new Tusk()
             << new Undying()
             << new VengefulSpirit()
             << new Zeus()

             << new ForceStaff()
             << new GemOfTrueSight()
             << new HelmOfTheDominator()
             << new UrnOfShadows();

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
