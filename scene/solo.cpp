#include "solo.h"
#include "view.h"
#include "menu.h"
#include "exam.h"

Q_GLOBAL_STATIC(Solo, solo)

Solo* Solo::instance()
{
    return solo();
}

void Solo::initialize()
{
    background = new Spirit(":/solo/0");
    addItem(background);
    background->setPos(0,0);

    button_0 = new Button(":/solo/99");
    addItem(button_0);
    button_0->setPos(24,477);
    connect(button_0, &Button::clicked, this, &Solo::go_home);

    button_1 = new Button(":/solo/1");
    button_1->setPos(190,45);
    addItem(button_1);
    connect(button_1, &Button::clicked, this, &Solo::go_exam);

    button_2 = new Button(":/solo/2");
    button_2->setPos(190,145);
    addItem(button_2);
    connect(button_2, &Button::clicked, this, &Solo::go_info);

    button_3 = new Button(":/solo/3");
    button_3->setPos(190,245);
    addItem(button_3);
    connect(button_3, &Button::clicked, this, &Solo::go_banlist);

    button_4 = new Button(":/solo/4");
    button_4->setPos(190,345);
    addItem(button_4);
    connect(button_4, &Button::clicked, this, &Solo::go_ai);

    button_5 = new Button(":/solo/5");
    button_5->setPos(190,445);
    addItem(button_5);
    connect(button_5, &Button::clicked, this, &Solo::go_custom);

    black = new BlackScreen;
    addItem(black);
    connect(black, &BlackScreen::show_over, this, &Solo::show_over);
    connect(black, &BlackScreen::hide_over, this, &Solo::hide_over);
}

void Solo::showScene()
{
    qView->setScene(this);
    black->showAnimation();
}

void Solo::show_over()
{
    button_0->setEnabled(true);
    button_1->setEnabled(true);
    button_2->setEnabled(true);
    button_3->setEnabled(true);
    button_4->setEnabled(true);
    button_5->setEnabled(true);
}

void Solo::hideScene()
{
    button_0->setEnabled(false);
    button_1->setEnabled(false);
    button_2->setEnabled(false);
    button_3->setEnabled(false);
    button_4->setEnabled(false);
    button_5->setEnabled(false);
    black->hideAnimation();
}

void Solo::hide_over()
{
    int index = button_index;
    button_index = -1;
    switch (index)
    {
    case -1:
        break;
    case 0:
        qMenu->showScene();
        break;
    case 1:
        qExam->showScene();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}

void Solo::go_home()
{
    button_index = 0;
    hideScene();
}

void Solo::go_exam()
{
    button_index = 1;
    hideScene();
}

void Solo::go_info()
{
    button_index = 2;
    hideScene();
}

void Solo::go_banlist()
{
    button_index = 3;
    hideScene();
}

void Solo::go_ai()
{
    button_index = 4;
    hideScene();
}

void Solo::go_custom()
{
    button_index = 5;
    hideScene();
}
