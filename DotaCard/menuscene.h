#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include "pixmap.h"
#include <QGraphicsSceneEvent>

class Menu : public Pixmap
{
    Q_OBJECT
public:
    Menu(const QString &filename, bool center_as_origin = true);
    void hover_duel_mode();
    void hover_card_check();
    void press_duel_mode();
    void press_card_check();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void timerEvent(QTimerEvent *);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    QPixmap pixmap;
    QRectF targetRect;
    QRectF sourceRect;
    int id1,id2;
    int x;
signals:
    void duel_mode();
    void card_check();
};

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MenuScene();
    Pixmap *back;
    Menu *menu;
signals:
    void duel_mode();
    void card_check();
};

#endif // MENUSCENE_H
