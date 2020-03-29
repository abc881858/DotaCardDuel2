#include "gif.h"

Gif::Gif(QStringList list)
    : Spirit(list.first()),
      m_list(list)
{
}

void Gif::show_animation()
{
    show();
    timer_id = startTimer(40);
    index = 0;
}

void Gif::timerEvent(QTimerEvent *)
{
    if(index==20)
    {
        hide();
        emit finished();
        killTimer(timer_id);
    }
    index++;
    setPixmap(m_list.at(index%5));
    update();
}
