#ifndef DOTA_H
#define DOTA_H

//给单例 Dota 设置一个宏，方便使用
#if defined(qDota)
#undef qDota
#endif
#define qDota (Dota::instance())

#include <QObject>
#include "card.h"
#include "room.h"
#include <QStack>

class Dota : public QObject
{
    Q_OBJECT
public:
    enum PhaseFlag
    {
        No_Phase,
        Draw_Phase,
        Standby_Phase,
        Main1_Phase,
        Battle_Phase,
        Main2_Phase,
        MyEnd_Phase,
        EnemyDraw_Phase,
        EnemyStandby_Phase,
        EnemyMain1_Phase,
        EnemyBattle_Phase,
        EnemyMain2_Phase,
        EnemyEnd_Phase
    };

    /*【咒文速度1】
     * 通常魔法 装备魔法 场地魔法 永续魔法 仪式魔法 效果怪兽
     * 咒文速度之中，速度最慢的一种
     * 不能够对应于其他卡的发动来做连锁的动作
     * 因此，基本上他不会成为连锁2以上的对应
     *
     *【咒文速度2】
     * 速攻魔法 通常陷阱 永续陷阱 效果怪兽（诱发即时效果）
     * 可以对应咒文速度1与咒文速度2而成为连锁的一个群集
     * 可以任意选择发动时机或是对手回合也可以发动的卡属于此类
     *
     * 【咒文速度3】
     * 反制陷阱
     * 可以对应任何速度以构成连锁，咒文速度最快的一种卡
     * 而能够对应它的卡也只有同样是咒文速度3的反制陷阱
    */

//Main阶段系统请求我主动发起: 改变阶段、召唤放置翻转怪兽、效果怪兽、通常魔法、速攻魔法、装备魔法
//Battle阶段系统请求我主动发起：攻击宣言, 速攻魔法卡
//对方阶段系统请求我主动发起：连锁=咒文速度2+3: 效果怪兽、速攻魔法、通常陷阱、永续陷阱、反击陷阱

    bool whoIsDoing; //是我方行动还是对方行动

//    QSound *music;

    static Dota* instance();
    void initialize();

    PhaseFlag phase; //我处于什么阶段

    bool firstTurn;
    bool oneTurnOneNormalSummon;

    QList<Card*> allCards;
    QList<Card*> enemyAllCards;
    QList<Card*> deckCards;
    QList<Card*> handCards;
    Card* fieldyardCards[5];
    Card* fieldgroundCards[5];
    QList<Card*> graveyardCards;
    QList<Card*> enemyDeckCards;
    QList<Card*> enemyHandCards;
    Card* enemyFieldyardCards[5];
    Card* enemyFieldgroundCards[5];
    QList<Card*> enemyGraveyardCards;

    Card::AreaFlag targetArea; //需要点击哪个场地的卡

    Card* attackSourceCard; //攻击来源的卡牌
    Card* attackDestinationCard; //攻击目标的卡牌
    Card* chainCard; //连锁的卡牌

    enum ReasonFlag //搜寻卡牌的原因
    {
        No_Reason,
        BeAttacked_Reason, //寻找被攻击的卡牌
        ChainDeclared_Reason, //寻找对方发动攻击宣言时，我方连锁的卡牌
        BeEquiped_Reason, //寻找被装备的怪兽卡
    };

    QStack<Dota::ReasonFlag> chainStack;

    Dota::ReasonFlag searchReason; //搜索 targetCard 的原因
    void setSearchReason(Dota::ReasonFlag flag); //同时设置检索条件
    Dota::ReasonFlag getSearchReason();

    int getCardIndexOfFieldyard(Card *card);
    int getCardIndexOfEnemyFieldyard(Card *card);
    int getCardIndexOfFieldground(Card *card);
    int getCardIndexOfEnemyFieldground(Card *card);
    int getCardIndexOfArea(Card *card, Card::AreaFlag flag);

    bool isSearchingTargetCard();
    bool authenticateCard(Card *card); //鉴权卡牌的总函数
    void addAuthenticateCardArea(Card::AreaFlag flag); //设置 鉴权 area

    void needAuthenticateCardActive();

    bool hasMonster();
    bool hasEnemyMonster();
//    Card *getEffectCard();
//    Card *getSelectCard();
//    void changeLp(bool isMine);
//    bool canActiveSpell();
    bool hasEmptyBackSlot();
    bool hasEmptyFrontSlot();

private:
    QSet<Card::AreaFlag> authenticateCardAreaList; // 鉴权 area
    bool authenticateCardActive; //需要 Card 能发动效果

};

#endif // DOTA_H
