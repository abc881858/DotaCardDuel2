#ifndef UNDYING_H
#define UNDYING_H

#include "effectmonstercard.h"

/*!
 * \brief 不朽尸王
 *
 * 一回合一次，3回合内使对方场上的一只怪兽守备力下降300点，这张卡的守备力上升300点。
 * 一回合一次，你可以弃一张手牌，在自己场上特殊召唤与对方场上怪兽数量相同的“僵尸衍生物”
 * （1星，不死族暗属性，攻500·守0，不能作为祭品、同调及超量素材，
 * 攻击对方守备力低于800的怪兽时，伤害计算阶段攻击力上升500，受到的战斗伤害为0。
 * 每进行一次攻击，伤害计算后被攻击怪兽攻·守下降200至你下回合结束。）
 *
 */

class Undying : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Undying();
};

#endif // UNDYING_H
