#ifndef BLACKSCREEN_H
#define BLACKSCREEN_H

#include "spirit.h"

class BlackScreen : public Spirit
{
    Q_OBJECT

public:
    BlackScreen();
    void showAnimation();
    void hideAnimation();

signals:
    void show_over();
    void hide_over();
};

#endif // BLACKSCREEN_H
