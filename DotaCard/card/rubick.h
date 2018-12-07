#ifndef RUBICK_H
#define RUBICK_H

#include "effectmonstercard.h"

/*!
 * \brief 大魔导师
 *
 * 这张卡在自己场上表侧表示存在时，自己场上名字带有“dota”的怪兽一回合一次不会被卡的效果破坏。
 * 一回合一次，选择一个效果发动：
 * 1、对方怪兽你的下回合开始前攻击力下降500；
 * 2、你获得对方的一个怪兽效果直到回合结束。当你装备“dota-阿哈利姆神杖”时，
 * 你的1、2效果可以同时发动且你的2效果1回合可以使用2次（覆盖上次获得的效果且该回合不能再次获得同一效果）
 *
 */

class Rubick : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Rubick();
};

#endif // RUBICK_H
