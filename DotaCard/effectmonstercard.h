#ifndef EFFECTMONSTERCARD_H
#define EFFECTMONSTERCARD_H

#include "card.h"

/*!
 * \brief 效果怪兽卡
 *
 */

class EffectMonsterCard : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE EffectMonsterCard();
    virtual bool testNormalSummon();
    virtual bool testAttack();
    virtual bool testSetCard();
    virtual bool testFlipSummon();
    virtual void standby();
    virtual bool testEffectFromFieldyard();
    bool canAttack;
    virtual void beforeActive();
    virtual void specialSummonCard();
    virtual void summonCard();
    virtual void setCard();
    virtual void gotoGraveyard(){}
};

#endif // EFFECTMONSTERCARD_H
