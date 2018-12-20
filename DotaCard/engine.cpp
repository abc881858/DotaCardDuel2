#include "engine.h"
#include "centaurwarrunner.h"
#include "keeperofthelight.h"
#include "lion.h"
#include "magnus.h"
#include "nyxassassin.h"
#include "rubick.h"
#include "tusk.h"
#include "undying.h"
#include "vengefulspirit.h"
#include "zeus.h"

#include "forcestaff.h"
#include "gemoftruesight.h"
#include "helmofthedominator.h"
#include "urnofshadows.h"

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
