#include "introduction.h"
#include <QTime>
#include "net.h"
#include "dota.h"
#include <QCursor>

#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

WelcomeScene::WelcomeScene()
{
    black = new Pixmap("title/black.jpg");
    first = new Pixmap("title/1.bmp");

    addItem(first);
    first->setPos(0,0);

    addItem(black);
    black->setPos(0,0);
}

void WelcomeScene::fade()
{
    QPropertyAnimation *fadeIn = new QPropertyAnimation(black,"opacity");
    fadeIn->setStartValue(1);
    fadeIn->setEndValue(0);
    fadeIn->setDuration(2000);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(black,"opacity");
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);
    fadeOut->setDuration(2000);

    auto *group = new QSequentialAnimationGroup;
    group->addAnimation(fadeIn);
    group->addAnimation(fadeOut);

    group->start(QAbstractAnimation::KeepWhenStopped);

    connect(group,SIGNAL(finished()),this,SIGNAL(changeScene()));
}

Welcome2Scene::Welcome2Scene()
{
    black = new Pixmap("title/black.jpg");
    second = new Pixmap("title/2.bmp");

    addItem(second);
    second->setPos(0,0);

    addItem(black);
    black->setPos(0,0);
}

void Welcome2Scene::fade()
{
    QPropertyAnimation *fadeIn = new QPropertyAnimation(black,"opacity");
    fadeIn->setStartValue(1);
    fadeIn->setEndValue(0);
    fadeIn->setDuration(2000);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(black,"opacity");
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);
    fadeOut->setDuration(2000);

    auto *group = new QSequentialAnimationGroup;
    group->addAnimation(fadeIn);
    group->addAnimation(fadeOut);

    group->start(QAbstractAnimation::DeleteWhenStopped);

    connect(group,SIGNAL(finished()),this,SIGNAL(changeScene2()));
}

Welcome3Scene::Welcome3Scene()
{
    black = new Pixmap("title/black.jpg");
    third = new Pixmap("title/3.bmp");

    addItem(third);
    third->setPos(0,0);

    addItem(black);
    black->setPos(0,0);
}

void Welcome3Scene::fade()
{
    QPropertyAnimation *fadeIn = new QPropertyAnimation(black,"opacity");
    fadeIn->setStartValue(1);
    fadeIn->setEndValue(0);
    fadeIn->setDuration(2000);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(black,"opacity");
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);
    fadeOut->setDuration(2000);

    auto *group = new QSequentialAnimationGroup;
    group->addAnimation(fadeIn);
    group->addAnimation(fadeOut);

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

Introduction::Introduction()
{
    qsrand(QVariant(QTime(0,0,0).secsTo(QTime::currentTime())).toUInt());
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setFrameStyle(QFrame::NoFrame);
    setFixedSize(QSize(800, 600));
    setSceneRect(0, 0, 800, 600);
    move(QPoint(0,0));

    welcome = new WelcomeScene;
    connect(welcome,SIGNAL(changeScene()),this,SLOT(changeScene()));

    welcome2 = new Welcome2Scene;
    connect(welcome2,SIGNAL(changeScene2()),this,SLOT(changeScene2()));

    welcome3 = new Welcome3Scene;

////    正式用
//    setScene(welcome);
//    welcome->fade();

//    测试用，直接进roomScene
    room = new Room;
    setScene(room);

    setCursor(QCursor(QPixmap(":/cursor/cur3"), 31, 15));
}

void Introduction::changeScene()
{
    setScene(welcome2);
    welcome2->fade();
}

void Introduction::changeScene2()
{
    qDota->initialize();

    menuscene = new MenuScene;
    setScene(menuscene);

//    qDota->music->play();

    menuscene->setFocus(Qt::MouseFocusReason);
//    connect(roomscene,SIGNAL(clear_all()),this,SLOT(change_all()));

    connect(menuscene, &MenuScene::duel_mode, [=](){
        qNet->initialize();
        setScene(room);
    });

    connect(menuscene, &MenuScene::card_check, [=](){
        deckscene = new DeckScene(this);
        connect(deckscene,&DeckScene::clicked, [=](){
            setScene(menuscene);
        });
        setScene(deckscene);
    });
}

void Introduction::change_all()
{
//    setScene(welcome3);
//    welcome3->fade();
//    music = new QSound("music/m_win.wav");
//    music->play();
}
