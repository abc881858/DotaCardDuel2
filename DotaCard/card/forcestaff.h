#ifndef FORCESTAFF_H
#define FORCESTAFF_H

#include "equipspellcard.h"

/*!
 * \brief 原力法杖
 *
 * 一回合一次，选择以下一项效果发动：
 * 1、对方发动没有将装备怪兽指定为对象的卡的效果时，
 * 装备怪兽不会受到那张卡的影响
 *
 * 2、自己场上一只怪兽成为攻击目标时，这次攻击不会破坏装备怪兽
 *
 * 3、自己场上一只怪兽攻击被无效时，
 * 可以令该怪兽对原目标怪兽再进行一次攻击
 *
 */

class ForceStaff : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE ForceStaff();
    virtual void standby();
    virtual void beforeActive();
    virtual bool testEffectFromFieldground();
    bool canEffect;
};

#endif // FORCESTAFF_H
