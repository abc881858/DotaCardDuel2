#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "effectmonster.h"

#define qGame (Game::instance())

class Game : public QObject
{
    Q_OBJECT

public:
    static Game* instance();
    void initialize();

    bool isMyturn{false};
    bool isMyMain{false};
    bool isMyAct{false};

    Card *activeCard{nullptr};

    void receiveActive(int effectIndex);

signals:
    //是否发动某一项技能
    void askWhetherActive(QString effectName);
    //选择发动某一项技能
    void askWhichActive(QStringList effectNames);
};

#endif // GAME_H
