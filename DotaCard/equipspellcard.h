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
    virtual bool testEffectFromFieldground();
    virtual void standby();
    virtual void afterEquip(){}
    virtual void active(){}
    virtual void unActive(){}
    virtual void doActive(){}
    virtual void beforeActive();
};

#endif // EQUIPSPELLCARD_H
