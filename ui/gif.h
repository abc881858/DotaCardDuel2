#ifndef GIF_H
#define GIF_H

#include "spirit.h"

class Gif : public Spirit
{
    Q_OBJECT

public:
    Gif(QStringList list);
    void show_animation();

protected:
    void timerEvent(QTimerEvent *);

private:
    QStringList m_list;
    int timer_id;
    int index{0};

signals:
    void finished();
};

#endif // GIF_H
