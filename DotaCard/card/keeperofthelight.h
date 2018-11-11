#ifndef KEEPEROFTHELIGHT_H
#define KEEPEROFTHELIGHT_H

#include "effectmonstercard.h"
/*!
 * \brief 光之守卫
 *
 * ①一回合一次，当有“dota-光之守卫”以外名字带有“dota”的加入手牌时可以发动，
 * 将那只怪兽特殊召唤至场上，若这张卡装备了“dota-阿哈利姆神杖”。
 * 则改此效果为：一回合一次，可以从手牌·卡组特殊召唤一只“dota-光之守卫”以外的名字带有“dota”的怪兽。
 *
 * ②这张卡在手牌存在时，一回合一次，将自己场上一只“dota-光之守卫”以外的名字带有“dota”的怪兽返回手牌。
 *
 * ③一回合一次，选择对方场上的一只怪兽发动，选择的怪兽在进行攻击宣言前必须丢弃一张手牌。
 *
 */

class KeeperoftheLight : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE KeeperoftheLight();
};

#endif // KEEPEROFTHELIGHT_H
