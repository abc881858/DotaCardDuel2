#include "menu.h"
#include <QDebug>
#include "view.h"
#include "training.h"
#include "solo.h"
#include "room.h"

Q_GLOBAL_STATIC(Menu, menu)

Menu* Menu::instance()
{
    return menu();
}

void Menu::initialize()
{
    background = new Spirit(":/menu/menu_main_0");
    addItem(background);
    background->setPos(0,0);

    button_1 = new Button(":/menu/menu_main_1");
    button_1->setPos(85,300);
    addItem(button_1);
    connect(button_1, &Button::clicked, this, &Menu::go_training);

    button_2 = new Button(":/menu/menu_main_2");
    button_2->setPos(250,300);
    addItem(button_2);
    connect(button_2, &Button::clicked, this, &Menu::go_solo);

    button_3 = new Button(":/menu/menu_main_3");
    button_3->setPos(415,300);
    addItem(button_3);
    connect(button_3, &Button::clicked, this, &Menu::go_rank_match);

    button_4 = new Button(":/menu/menu_main_4");
    button_4->setPos(590,300);
    addItem(button_4);

    black = new BlackScreen;
    addItem(black);
    connect(black, &BlackScreen::show_over, this, &Menu::show_over);
    connect(black, &BlackScreen::hide_over, this, &Menu::hide_over);
    black->hide();
}

void Menu::showScene()
{
    qView->setScene(this);
    black->showAnimation();
}

void Menu::show_over()
{
    button_1->setEnabled(true);
    button_2->setEnabled(true);
    button_3->setEnabled(true);
    button_4->setEnabled(true);
}

void Menu::hideScene()
{
    button_1->setEnabled(false);
    button_2->setEnabled(false);
    button_3->setEnabled(false);
    button_4->setEnabled(false);
    black->hideAnimation();
}

void Menu::hide_over()
{
    int index = button_index;
    button_index = -1;
    switch (index)
    {
    case -1:
        break;
    case 0:
        break;
    case 1:
        qTraining->showScene();
        break;
    case 2:
        qSolo->showScene();
        break;
    case 3:
        qRoom->showScene();
        break;
    case 4:
        break;
    }
}

void Menu::go_training()
{
    button_index = 1;
    hideScene();
}

void Menu::go_solo()
{
    button_index = 2;
    hideScene();
}

void Menu::go_rank_match()
{
    button_index = 3;
    hideScene();
}
