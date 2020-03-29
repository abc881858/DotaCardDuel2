#ifndef EFFECTMONSTER_H
#define EFFECTMONSTER_H

#include <card.h>

struct ActiveEffect
{
    QString name; //主动发动的效果名字
    bool isOnce; //是否一回合一次
    bool hasActived; //是否已经发动过
};

//struct PassiveEffect
//{
//    QString name; //被动发动的效果名字
//};

class EffectMonster : public Card
{
public:
    EffectMonster();
    virtual bool testActive();

    bool isForbidden{false};

    QList<ActiveEffect*> activeList;
//    QList<PassiveEffect> passiveList;
};

#endif // EFFECTMONSTER_H
