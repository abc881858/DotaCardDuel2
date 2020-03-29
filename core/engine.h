#ifndef ENGINE_H
#define ENGINE_H

#define qEngine (Engine::instance())

#include <QHash>
#include <QList>
#include <QMetaObject>
#include "card.h"

class Engine
{
public:
    static Engine* instance();
    void initialize();
    Card* cloneCard(int ISDN);

private:
    QHash<int, const QMetaObject*> metaobjects;
    QList<Card*> allclass;
};

#endif // ENGINE_H
