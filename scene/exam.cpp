#include "exam.h"
#include "view.h"
#include "menu.h"
#include <QKeyEvent>
#include "examfirst.h"

Q_GLOBAL_STATIC(Exam, exam)

Exam* Exam::instance()
{
    return exam();
}

void Exam::initialize()
{
    background = new Spirit(":/exam/0");
    addItem(background);
    background->setPos(0,0);

    button_1 = new Button(":/exam/1");
    button_1->setPos(47,54);
    addItem(button_1);
    connect(button_1, &Button::clicked, this, &Exam::go_exam1);

    button_2 = new Button(":/exam/2");
    button_2->setPos(47,237);
    addItem(button_2);
    connect(button_2, &Button::clicked, this, &Exam::go_exam2);

    button_3 = new Button(":/exam/3");
    button_3->setPos(47,417);
    addItem(button_3);
    connect(button_3, &Button::clicked, this, &Exam::go_exam3);

    button_4 = new Button(":/exam/4");
    button_4->setPos(293,50);
    addItem(button_4);
    connect(button_4, &Button::clicked, this, &Exam::go_exam4);

    button_5 = new Button(":/exam/5");
    button_5->setPos(293,232);
    addItem(button_5);
    connect(button_5, &Button::clicked, this, &Exam::go_exam5);

    button_6 = new Button(":/exam/6");
    button_6->setPos(293,423);
    addItem(button_6);
    connect(button_6, &Button::clicked, this, &Exam::go_exam6);

    button_7 = new Button(":/exam/7");
    button_7->setPos(581,75);
    addItem(button_7);
    connect(button_7, &Button::clicked, this, &Exam::go_exam7);

    black = new BlackScreen;
    addItem(black);
    connect(black, &BlackScreen::show_over, this, &Exam::show_over);
    connect(black, &BlackScreen::hide_over, this, &Exam::hide_over);
}

void Exam::showScene()
{
    qView->setScene(this);
    black->showAnimation();
}

void Exam::show_over()
{
    button_1->setEnabled(true);
    button_2->setEnabled(true);
    button_3->setEnabled(true);
    button_4->setEnabled(true);
    button_5->setEnabled(true);
    button_6->setEnabled(true);
    button_7->setEnabled(true);
    active_key_escape = true;
}

void Exam::hideScene()
{
    button_1->setEnabled(false);
    button_2->setEnabled(false);
    button_3->setEnabled(false);
    button_4->setEnabled(false);
    button_5->setEnabled(false);
    button_6->setEnabled(false);
    button_7->setEnabled(false);
    black->hideAnimation();
}

void Exam::hide_over()
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
        qExamFirst->showScene();
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

void Exam::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if(button_index == -1)
    {
        return;
    }
    if(keyEvent->key() == Qt::Key_Escape)
    {
        button_index = 0;
        hideScene();
    }
}

void Exam::go_exam1()
{
    button_index = 1;
    hideScene();
}

void Exam::go_exam2()
{

}

void Exam::go_exam3()
{

}

void Exam::go_exam4()
{

}

void Exam::go_exam5()
{

}

void Exam::go_exam6()
{

}

void Exam::go_exam7()
{

}
