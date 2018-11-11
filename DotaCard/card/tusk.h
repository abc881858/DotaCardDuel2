#ifndef TUSK_H
#define TUSK_H

#include "effectmonstercard.h"

/*!
 * \brief 巨牙海民
 *
 * 这张卡在进行攻击时，可以从手牌表侧攻击特殊召唤一只名字带有“dota”的怪兽，
 * 伤害计算阶段，这张卡的攻击力上升特殊召唤的怪兽攻击力的一半，
 * 这回合，由这个效果特殊召唤而来的怪兽不需要装备“dota-跳刀”便可以发动装备“dota-跳刀”的效果。
 * 一回合一次，这张卡攻击时，若目标怪兽的防御力低于你的攻击力，此次战斗对对方造成的战斗伤害翻倍。
 *
 */

class Tusk : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Tusk();
};

#endif // TUSK_H
