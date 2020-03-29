#include "training.h"
#include "view.h"
#include "menu.h"

Q_GLOBAL_STATIC(Training, training)

Training* Training::instance()
{
    return training();
}

void Training::initialize()
{
    background = new Button(":/training/0");
    addItem(background);
    background->setPos(0,0);
    background->setEnabled(false);
    connect(background, &Button::clicked, this, &Training::clicked);

    black = new BlackScreen;
    addItem(black);
    connect(black, &BlackScreen::show_over, this, &Training::show_over);
    connect(black, &BlackScreen::hide_over, this, &Training::hide_over);
}

void Training::showScene()
{
    index = 0;
    background->setPixmap(QString(":/training/").append(QString::number(index)));
    qView->setScene(this);
    black->showAnimation();
}

void Training::hideScene()
{
    background->setEnabled(false);
    black->hideAnimation();
}

void Training::show_over()
{
    background->setEnabled(true);
}

void Training::hide_over()
{
    qMenu->showScene();
}

void Training::clicked()
{
    index++;
    if(index == 4)
    {
        hideScene();
        return;
    }
    background->setPixmap(QString(":/training/").append(QString::number(index)));
    update();
}
