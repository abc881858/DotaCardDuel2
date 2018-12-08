#ifndef HELMOFTHEDOMINATOR_H
#define HELMOFTHEDOMINATOR_H

#include "equipspellcard.h"

/*!
 * \brief 支配头盔
 *
 * ①装备怪兽守备力上升300
 *
 * ②装备怪兽对对方造成战斗伤害时，装备怪兽的控制者回复
 * 那个战斗伤害的数值一半的基本分。
 *
 * ③一回合一次，选择自己卡组的一只3星以下的怪兽特殊召唤。
 * 当这张装备卡从场上离开或再次使用该效果时，召唤怪兽破坏。
 *
 * ④这张卡从场上送去墓地时，
 * 从卡组·墓地将一张“撒旦之邪力”加入手牌。
 *
 */

class HelmOfTheDominator : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE HelmOfTheDominator();
    virtual void standby();
    virtual void active();
    virtual bool testEffectFromFieldground();
    bool canEffect;
    virtual void activeAfterEquiped();
};

#endif // HELMOFTHEDOMINATOR_H
