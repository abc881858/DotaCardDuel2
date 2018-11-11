#ifndef NYXASSASSIN_H
#define NYXASSASSIN_H

#include "effectmonstercard.h"

/*!
 * \brief 地穴刺客
 *
 * ①一回合一次，丢弃一张手牌，指定对方场上一只表侧表示的怪兽发动，
 * 对方受到怪兽等级的一半（向下取整且最少为1）*400点伤害，并丢弃一张手牌。
 *
 * ②这张卡有一次不会被破坏，并破坏的种类发动以下效果。
 * 战斗破坏：给与攻击怪兽控制者等同于攻击怪兽攻击的伤害。
 * 效果破坏：破坏那张卡，若那张卡需要指定的怪兽在场上才能发动，则指定的怪兽一起破坏。
 *
 * ③一回合一次，丢弃一张手卡发动，这张卡在下次攻击的伤害计算阶段结束前攻击力上升600，且不会成为攻击和卡的效果对象。
 *
 */

class NyxAssassin : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE NyxAssassin();
};

#endif // NYXASSASSIN_H
