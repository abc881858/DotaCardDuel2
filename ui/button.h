#ifndef BUTTON_H
#define BUTTON_H

#include "spirit.h"

class Button : public Spirit
{
    Q_OBJECT

public:
    using Spirit::Spirit;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

signals:
    void hoverEnter();
    void hoverLeave();
    void clicked();
};

#endif // BUTTON_H
