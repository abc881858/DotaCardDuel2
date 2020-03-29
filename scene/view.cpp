#include "view.h"

Q_GLOBAL_STATIC(View, view)

View* View::instance()
{
    return view();
}

void View::initialize()
{
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setFrameStyle(QFrame::NoFrame);
    setFixedSize(QSize(800, 600));
    setSceneRect(0, 0, 800, 600);
    move(QPoint(0,0));
}
