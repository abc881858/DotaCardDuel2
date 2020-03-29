#ifndef TRAINING_H
#define TRAINING_H

#include <QGraphicsScene>
#include "blackscreen.h"
#include "button.h"

#define qTraining (Training::instance())

class Training : public QGraphicsScene
{
    Q_OBJECT

public:
    static Training* instance();
    void initialize();
    Button *background;
    BlackScreen *black;
    void showScene();
    void hideScene();

private:
    int index{0};

public slots:
    void show_over();
    void hide_over();
    void clicked();
};

#endif // TRAINING_H
