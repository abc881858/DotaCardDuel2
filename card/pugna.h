#ifndef PUGNA_H
#define PUGNA_H

#include "effectmonster.h"

class Pugna : public EffectMonster
{
    Q_OBJECT

public:
    Q_INVOKABLE Pugna();
    void active();
    void passive();
    int checkEffect();

    bool testActive();
};

#endif // PUGNA_H
