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
#include "structs.h"

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


    enum AreaFlag
    {
        No_Area,
        Deck_Area,
        Hand_Area,
        Fieldyard_Area,
        Fieldground_Area,
        Graveyard_Area,
        EnemyDeck_Area,
        EnemyHand_Area,
        EnemyFieldyard_Area,
        EnemyFieldground_Area,
        EnemyGraveyard_Area
    };

    static Dota* instance();
    void initialize();

    PhaseFlag phase; //我处于什么阶段

    bool firstTurn;
    bool oneTurnOneNormalSummon;

//    QList<Card*> allCards;
//    QList<Card*> allEnemyCards;
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
    Card* hoverCard;
    Card* equipSpellCard; //装备魔法卡牌
    Card* equipMonsterCard; //装备怪兽卡牌

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

    int getCardIndex(Card *card);

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

public slots:
    void response_setupDeck();
    void response_startGame(QJsonObject json);
    void response_enemyStartGame();
    void response_drawPhase();
    void response_standbyPhase();
    void response_main1Phase();
    void response_endPhase();
    void response_enemySetupDeck(QJsonObject json);
    void response_enemyDrawPhase();
    void response_enemyStandbyPhase();
    void response_enemyMain1Phase();
    void response_enemyBattlePhase();
    void response_enemyMain2Phase();
    void response_enemyEndPhase();

    void response_enemyBeEquiped(QJsonObject json);
    void response_enemyBeAttack(QJsonObject json);
    void response_finishChain();

    void response_enemyChained(QJsonObject json);

    void response_moveCard(QJsonObject json);

signals:
    void moveCardItem(CardMoveStruct);
    void goBattlePhase(QList<int>);
    void goMain2Phase();
    void goEndPhase();
    void goDrawPhase();
    void goStartGame();
    void goStandbyPhase();
    void goMain1Phase();

    void createCardItem(int);
    void createEnemyCardItem(int);

    void showAttackAnimation(int, int);
    void showEnemyAttackAnimation(int, int);
    void showChainAnimation(int, int);

public:
    void setupConnect(QList<Card *> list, bool enemy);
    int testPlace(Card::AreaFlag flag);
    void moveCard(CardMoveStruct move);
    void goStartPhase();
    void activeSpellCard(Card *card);
    void specialSummonCard(Card *card);
    void summonCard(Card *card);
    void setCard(Card *card);

    void tryGoBattlePhase();
    void tryGoMain2Phase();
    void tryGoEndPhase();
    Card *getCardFromIndex(int index);
    Card *getEnemyCardFromIndex(int index);
    void chain(int number);

    void chainDeclared();
    void attack(Card *card);
    void beAttacked();
    void beEquiped();
};

#endif // DOTA_H
