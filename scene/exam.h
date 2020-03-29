#ifndef EXAMINE_H
#define EXAMINE_H

#include <QGraphicsScene>
#include "blackscreen.h"
#include "button.h"
#include "spirit.h"

#define qExam (Exam::instance())

class Exam : public QGraphicsScene
{
    Q_OBJECT

public:
    static Exam* instance();
    void initialize();
    Spirit *background;

    Button *button_1;
    Button *button_2;
    Button *button_3;
    Button *button_4;
    Button *button_5;
    Button *button_6;
    Button *button_7;

    BlackScreen *black;
    void showScene();

protected:
    void keyReleaseEvent(QKeyEvent *keyEvent);

private:
    bool active_key_escape{true};
    int button_index{-1};
    void hideScene();

public slots:
    void show_over();
    void hide_over();
    void go_exam1();
    void go_exam2();
    void go_exam3();
    void go_exam4();
    void go_exam5();
    void go_exam6();
    void go_exam7();
};

#endif // EXAMINE_H
