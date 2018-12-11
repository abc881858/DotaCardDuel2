#ifndef SATANIC_H
#define SATANIC_H

#include "equipspellcard.h"

/*!
 * \brief 撒旦之邪力
 *
 * ① 装备怪兽攻击力上升400，守备力上升700
 *
 * ② 装备怪兽对对方造成战斗伤害时，回复战斗伤害一半的基本分
 *
 * ③ 2回合一次，伤害计算阶段，可以使装备怪兽攻击力
 * 或守备力上升与对方怪兽攻击力的差值的2倍
 * 回复此差值2倍的基本分
 *
 */

class Satanic : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Satanic();
    virtual void standby();
    virtual void tryActive();
    virtual bool testEffectFromFieldground();
    bool canEffect;
};

#endif // SATANIC_H
