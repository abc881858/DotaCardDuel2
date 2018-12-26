#ifndef AGHANIMSSCEPTER_H
#define AGHANIMSSCEPTER_H

#include "equipspellcard.h"

/* 遊戲王
 * \brief 阿哈利姆神杖
 *
 * 装备怪兽攻·守上升300点。装备怪兽因为自己场上的卡的效果或发动卡的效果
 * 而被送去墓地导致这张卡被破坏的场合，这张卡回到手牌。
 *
 */

class AghanimsScepter : public EquipSpellCard
{
    Q_OBJECT
public:
    Q_INVOKABLE AghanimsScepter();
    virtual void afterEquip();
};

#endif // AGHANIMSSCEPTER_H
