#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

#define qView (View::instance())

class View : public QGraphicsView
{
    Q_OBJECT

public:
    static View* instance();
    void initialize();
};

#endif // VIEW_H
