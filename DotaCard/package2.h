#ifndef PACKAGE2_H
#define PACKAGE2_H

#include "card.h"

//DoubleDamage 双倍伤害神符

//选择自己场上一只怪兽发动
//选择的怪兽的原本攻击力变为2倍
//该buff持续至当前回合结束（即半个回合）

class DoubleDamageRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE DoubleDamageRune();
//    virtual void effect();
};

//Haste 急速神符

//选择自己场上一只怪兽发动
//选择的怪兽一回合一次，可以无效一次以该怪兽为目标的攻击
//战斗阶段，选择的怪兽可以做2次攻击
//该buff持续2个回合

class HasteRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE HasteRune();
//    virtual void effect();
};

//Illusion 幻象神符

//选择自己场上一只怪兽发动
//在自己场上特殊召唤2只“幻象神符token”
//等级属性种族和指定怪兽相同，攻击力和守备力为指定怪兽当前攻击力守备力的一半，不能用作祭品，
//这个效果召唤的“幻象神符token”在你下回合结束后破坏（即1个半回合）

class IllusionRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE IllusionRune();
//    virtual void effect();
};

//Invisibility 隐身神符

//选择自己场上一只怪兽发动
//对方无法对该怪兽发动攻击，对方无法对该怪兽发动效果
//该buff持续至你的下回合结束（即1个半回合）
//若中途选择的怪兽进行了攻击宣言或者发动了怪兽效果，则该buff提前结束

class InvisibilityRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE InvisibilityRune();
//    virtual void effect();
};

//Regeneration 恢复神符

//选择自己场上一只怪兽发动
//每个回合结束时，回复选择怪兽守备力一半数值的基本分并抽一张卡
//该buff持续3个回合
//若中途选择的怪兽进行了战斗，则该buff提前结束

class RegenerationRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE RegenerationRune();
//    virtual void effect();
};

//Bounty 赏金神符

//选择自己场上一只怪兽发动
//从卡组中选择一张卡加入手牌，该卡这回合不能使用

class BountyRune : public Card
{
    Q_OBJECT
public:
    Q_INVOKABLE BountyRune();
//    virtual void effect();
};


#endif // PACKAGE2_H
