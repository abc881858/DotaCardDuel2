#ifndef GEMOFTRUESIGHT_H
#define GEMOFTRUESIGHT_H

#include "equipspellcard.h"

/*!
 * \brief 真视宝石
 *
 * 只要这张卡在场上存在，对方场上所有带有“不能成为攻击对象”和
 * “不能成为卡的效果对象”的效果的卡此效果无效，装备怪兽被破坏时，
 * 这张卡加入对方手牌
 *
 */

class GemOfTrueSight : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE GemOfTrueSight();
    virtual void standby();
};

#endif // GEMOFTRUESIGHT_H
