#ifndef URNOFSHADOWS_H
#define URNOFSHADOWS_H

#include "equipspellcard.h"

/*!
 * \brief 影之灵龛
 *
 * ①装备怪兽守备力上升100
 *
 * ②对方场上每有一只怪兽被破坏，便给这张卡放置一个“能量指示物”，
 * 若这张卡没有“能量指示物”，
 * 则可以额外放置一个。
 *
 * ③选择场上一只表侧表示的怪兽并去除这张卡上的一个“能量指示物”发动，
 * 选择的怪兽若是我方怪兽，
 * 则使其守备力上升300点直到回合结束。
 * 若为对方怪兽，则使其攻击力下降300点直到回合结束。
 * 这个效果可以在对方回合发动。
 *
 */

class UrnOfShadows : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE UrnOfShadows();
    virtual void standby();
    int marker{0};
    virtual void afterEquip();
};

#endif // URNOFSHADOWS_H
