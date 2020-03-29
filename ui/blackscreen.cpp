#include "blackscreen.h"
#include <QPropertyAnimation>

BlackScreen::BlackScreen()
    : Spirit(":/training/black")
{
    setPos(0,0);
}

void BlackScreen::showAnimation()
{
    auto *fadeOut = new QPropertyAnimation(this,"opacity");
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->setDuration(500);

    connect(fadeOut,SIGNAL(finished()),this,SIGNAL(show_over()));

    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
}

void BlackScreen::hideAnimation()
{
    show();
    auto *fadeIn = new QPropertyAnimation(this,"opacity");
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);
    fadeIn->setDuration(500);

    connect(fadeIn,SIGNAL(finished()),this,SIGNAL(hide_over()));

    fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
}
