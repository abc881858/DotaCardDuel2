#ifndef ZEUS_H
#define ZEUS_H

#include "effectmonstercard.h"

/*!
 * \brief 奥林匹斯之王
 *
 * ①当自己场上存在“dota-奥林匹斯之王”以外名字带有“dota”的怪兽时，这张卡可以从手牌特殊召唤。
 *
 * ②一回合一次，丢弃一张手牌发动，破坏对方场上一只怪兽。
 *
 * ③一回合一次，丢弃2张手牌发动，对方场上怪兽守备力降低1000点，因此效果使怪兽守备力降低至0的场合，破坏此怪兽。
 * 若这张卡装备了“dota-阿哈利姆神杖”时，改为降低2000点守备力。
 *
 */

class Zeus : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE Zeus();
};

#endif // ZEUS_H
