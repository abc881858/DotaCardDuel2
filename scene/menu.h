#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include "button.h"
#include "blackscreen.h"

#define qMenu (Menu::instance())

class Menu : public QGraphicsScene
{
    Q_OBJECT

public:
    static Menu* instance();
    void initialize();
    Spirit *background;
    Button *button_1;
    Button *button_2;
    Button *button_3;
    Button *button_4;
    BlackScreen *black;
    void showScene();

private:
    int button_index{-1};
    void hideScene();

public slots:
    void show_over();
    void hide_over();
    void go_training();
    void go_solo();
    void go_rank_match();
};

#endif // MENU_H
