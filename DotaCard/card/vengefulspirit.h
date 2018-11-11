#ifndef VENGEFULSPIRIT_H
#define VENGEFULSPIRIT_H

#include "effectmonstercard.h"

/*!
 * \brief 复仇之魂
 *
 * ①当自己场上有“dota-复仇之魂”外的名字带有“dota”怪兽时发动。
 * 你选择一名对方4星以下的怪兽，这张卡和该怪兽的控制权交换直到回合结束，
 * 交换控制权的怪兽不能作为祭品，也不能进行攻击。
 * 若这张卡装备了“dota-阿哈利姆神杖”则可以指定对方任何怪兽且不需要自己场上存在名字带有“dota”的怪兽，
 * 当这张卡的控制权转移给对方时，你可以令这张卡装备的“dota-阿哈利姆神杖”回到手牌。
 *
 * ②只要这张卡在场上，名字带有“dota”的怪兽攻击力上升300。
 *
 * ③一回合一次，你可以指定一名怪兽使其防御力降低800。
 *
 */

class VengefulSpirit : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE VengefulSpirit();
};

#endif // VENGEFULSPIRIT_H
