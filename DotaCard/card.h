#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card();
    friend class CardItem;
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
    enum KindFlag
    {
        No_Kind,
        NormalMonster_Kind,
        EffectMonster_Kind,
        NormalSpell_Kind,
        ContinuousSpell_Kind,
        EquipSpell_Kind,
        QuicklyplaySpell_Kind,
        FieldSpell_Kind,
        NormalTrap_Kind,
        ContinuousTrap_Kind,
        CounterTrap_Kind
    };
    enum AttributeFlag
    {
        No_Attribute,
        Earth_Attribute, //地
        Water_Attribute, //水
        Fire_Attribute, //火
        Wind_Attribute, //风
        Light_Attribute, //光
        Dark_Attribute //暗
    };

    //Type：Dragon（龙族）、Spellcaster（魔法使族）、Zombie（不死族）、Warrior（战士族）、
    //BeastWarrior（兽战士族）、Beast（兽族）、WingedBeast（鸟兽族）、Fiend（恶魔族）、
    //Fairy（天使族）、Insect（昆虫族）、Dinosaur（恐龙族）、Reptile（爬虫族）、Fish（鱼族）、
    //SeaSerpent（海龙族）、Machine（机械族）、Thunder（雷族）、Aqua（水族）、Pyro（炎族）、
    //Rock（岩石族）、Plant（植物族）
    enum TypeFlag
    {
        No_Type,
        Dragon_Type,
        Spellcaster_Type,
        Zombie_Type,
        Warrior_Type,
        BeastWarrior_Type,
        Beast_Type,
        WingedBeast_Type,
        Fiend_Type,
        Fairy_Type,
        Insect_Type,
        Dinosaur_Type,
        Reptile_Type,
        Fish_Type,
        SeaSerpent_Type,
        Machine_Type,
        Thunder_Type,
        Aqua_Type,
        Pyro_Type,
        Rock_Type,
        Plant_Type
    };

    virtual void standby();

    virtual bool testEffectFromHand();
    virtual bool testSpecialSummon();
    virtual bool testNormalSummon();
    virtual bool testSetCard();
    virtual bool testEffectFromFieldyard();

    virtual bool testDefencePosition();
    virtual bool testAttackPosition();
    virtual bool testFlipSummon();
    virtual bool testEffectFromFieldground();
    virtual bool testAttack();

    virtual void active();

    int getISDN() const;
    KindFlag getKind() const;

    bool getFace() const;

    void setupCard();
    void enemySetupCard();
    void drawCard();
    void enemyDrawCard();
    void specialSummonCard();
    void enemySpecialSummonCard();
    void summonCard();
    void enemySummonCard();
    void activeCard();
    void enemyActiveCard();
    void setCard();
    void enemySetCard();

    AreaFlag getArea() const;

    void destroyCard();
    void enemyDestroyCard();

    void setArea(const AreaFlag &value);

    bool getStand() const;
    void setStand(bool value);

    int getATK() const;
    void setATK(int value);

    bool canAttack;

    QList<Card*> equipSpellCards;//装备了几张魔法卡
    Card* equipMonsterCard;//被装备在哪张怪兽卡上

protected:
    bool face; //表侧 里侧
    bool stand; //攻击 防守
    bool enemy; //是否在对方场上
    AreaFlag area;
    int count_turn; //在场几回合

    int ISDN;
    KindFlag kind; //怪兽魔法陷阱
    AttributeFlag attribute; //光暗属性
    TypeFlag type; //种族
    int level; //等级
    int ATK; //原始攻击力
    int DEF; //原始防御力
    int currentATK; //当前攻击力
    int currentDEF; //当前防御力
    QString name; //图片名字
    QString description; //卡牌描述

};

#endif // CARD_H
