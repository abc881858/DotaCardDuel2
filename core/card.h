#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
    Q_OBJECT

public:
    explicit Card();

    enum AreaFlag
    {
        No_Area,
        Deck_Area,
        Hand_Area,
        Front_Area,
        Back_Area,
        Grave_Area,
        Remote_Deck_Area,
        Remote_Hand_Area,
        Remote_Front_Area,
        Remote_Back_Area,
        Remote_Grave_Area
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

    int getISDN() const{return ISDN;}
    void setISDN(int value){ISDN = value;}

    AreaFlag getArea() const{return area;}
    void setArea(AreaFlag value){area = value;}

    bool getFace() const{return face;}
    void setFace(bool value){face = value;}

    bool getStand() const{return stand;}
    void setStand(bool value){stand = value;}

    QString getName() const{return name;}
    void setName(const QString &value){name = value;}

    virtual bool testActive();

protected:
    int ISDN{0}; //card ID
    QString name{"No_Name"}; //图片名字
    QString description{"No_Description"}; //卡牌描述
    AttributeFlag attribute{No_Attribute}; //光暗属性
    int level{0}; //等级
    KindFlag kind{No_Kind}; //Monster or Spell
    TypeFlag type{No_Type}; //种族
    int ATK{-1}; //原始攻击力
    int DEF{-1}; //原始防御力
    AreaFlag area{No_Area};

    bool face{false}; //表侧 里侧
    bool stand{true}; //攻击 防守

    //    bool enemy; //是否在对方场上
    //    int count_turn; //在场几回合
    //    int currentATK; //当前攻击力
    //    int currentDEF; //当前防御力
};

class CardMoveStruct
{
public:
    CardMoveStruct()
    {
        areaFrom = Card::No_Area;
        areaTo = Card::No_Area;
        indexFrom = -1;
        indexTo = -1;
        //    reason = REASON_unknown;
    }
    Card::AreaFlag areaFrom;
    Card::AreaFlag areaTo;
    int indexFrom;
    int indexTo;
};

#endif // CARD_H
