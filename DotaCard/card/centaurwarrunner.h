#ifndef CENTAURWARRUNNER_H
#define CENTAURWARRUNNER_H

#include "effectmonstercard.h"

/*!
 * \brief 半人马酋长
 *
 * ①将这张卡作为祭品发动，强制结束对方的战斗阶段。
 * 若这张卡装备了“dota-跳刀”，
 * 则可以改为丢弃一张手牌发动
 *
 * ②你的每回合一次，在对方场合也可以发动
 * 你可以让自己场上名字带有“dota”的怪兽全部变为攻击表示或防守表示，
 * 若这张卡装备了“dota-阿哈利姆神杖”时，
 * 同时令自己场上名字带有“dota”的怪兽的攻击力（或防御力）上升自己
 * 原本攻击力（或防御力）的一半。
 *
 */

class CentaurWarrunner : public EffectMonsterCard
{
    Q_OBJECT
public:
    Q_INVOKABLE CentaurWarrunner();
    virtual int testEffectFromFieldyard();
    virtual void standby();
private:
    bool oneTurnEffect2;
};

#endif // CENTAURWARRUNNER_H
