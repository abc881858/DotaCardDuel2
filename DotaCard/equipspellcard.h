#ifndef EQUIPSPELLCARD_H
#define EQUIPSPELLCARD_H

#include "card.h"

/*!
 * \brief 装备魔法卡
 *
 */

class EquipSpellCard : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE EquipSpellCard();
    virtual bool testEffectFromHand();
    virtual int testEffectFromFieldyard();
    virtual void standby();
    virtual void activeEffect();
    virtual void active();
private:
    bool oneTurnEffect3;
};

#endif // EQUIPSPELLCARD_H
