#ifndef SOLO_H
#define SOLO_H

#include <QGraphicsScene>
#include "blackscreen.h"
#include "button.h"
#include "spirit.h"

#define qSolo (Solo::instance())

class Solo : public QGraphicsScene
{
    Q_OBJECT

public:
    static Solo* instance();
    void initialize();
    Spirit *background;
    Button *button_0;
    Button *button_1;
    Button *button_2;
    Button *button_3;
    Button *button_4;
    Button *button_5;
    BlackScreen *black;
    void showScene();

private:
    int button_index{-1};
    void hideScene();

public slots:
    void show_over();
    void hide_over();
    void go_home();
    void go_exam();
    void go_info();
    void go_banlist();
    void go_ai();
    void go_custom();
};

#endif // SOLO_H
