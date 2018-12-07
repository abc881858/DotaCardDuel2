#ifndef MAGNUS_H
#define MAGNUS_H

#include "effectmonstercard.h"

/*!
 * \brief 半人猛犸
 *
 * ①一回合一次，令自己场上一只名字带有“dota”的怪兽，
 * 在你下回合开始前攻击力上升400点，且在攻击之后，
 * 可以降低600点攻击对对方场上所有怪兽进行一次攻击。
 *
 * ②将这张卡装备的“dota-跳刀”送去墓地，
 * 将对方场上的怪兽全部转为正面攻击表示，攻击力变为0，
 * 且在对方回合结束前不能进行攻击不能更变形式。
 *
 */

class Magnus : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Magnus();
};

#endif // MAGNUS_H
