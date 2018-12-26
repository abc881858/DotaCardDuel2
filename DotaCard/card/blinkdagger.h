#ifndef BLINKDAGGER_H
#define BLINKDAGGER_H

#include "equipspellcard.h"

/*
 * \brief 跳刀
 *
 * ①装备怪兽攻击力上升200
 *
 * ②选择场上的1只5星以下的衍生物发动，破坏那只怪兽，抽一张卡。
 * 这个效果在3回合后才能再次使用
 *
 */

class BlinkDagger : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE BlinkDagger();
    virtual void afterEquip();
};

#endif // BLINKDAGGER_H
