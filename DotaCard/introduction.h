#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QtMultimedia/QSound>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "pixmap.h"
#include "menuscene.h"
#include "deckscene.h"
#include "room.h"

class WelcomeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    WelcomeScene();
    Pixmap *black;
    Pixmap *first;

    void fade();

signals:
    void changeScene();
};

class Welcome2Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Welcome2Scene();
    Pixmap *black;
    Pixmap *second;
    void fade();
signals:
    void changeScene2();
};

class Welcome3Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Welcome3Scene();
    Pixmap *black;
    Pixmap *third;
    void fade();
};

class Introduction : public QGraphicsView
{
    Q_OBJECT
public:
    Introduction();
    QSound *music{};
private:
    MenuScene *menuscene{};
    WelcomeScene *welcome;
    Welcome2Scene *welcome2;
    Welcome3Scene *welcome3;
    DeckScene *deckscene{};
    Room *room;
public slots:
    void changeScene();
    void changeScene2();
    void change_all();
};

#endif // INTRODUCTION_H
