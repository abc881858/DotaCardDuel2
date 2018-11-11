#ifndef LION_H
#define LION_H

#include "effectmonstercard.h"

/*!
 * \brief 恶魔巫师
 *
 * 一回合一次，选择下面的其一的效果发动：
 * 1、选择对方场上一张怪兽发动，选择的怪兽变为里侧守备表示。
 * 2、选择对方场上一张里侧守备表示的怪兽发动，选择的怪兽破坏。
 * 当这张卡装备了“dota-阿哈利姆神杖”时，同时破坏选择怪兽两边的卡。
 *
 */

class Lion : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Lion();
};

#endif // LION_H
