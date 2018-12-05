#include "menuscene.h"
#include <QGraphicsProxyWidget>
#include <QTimerEvent>

Menu::Menu(const QString &filename, bool center_as_origin)
    : Pixmap(filename, center_as_origin), pixmap(QString("title/menu_e_ani0.bmp"))
{
    setAcceptHoverEvents(true);
    id1 = 0;
    id2 = 0;
    x = 0;
}

void Menu::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qreal pos_y = event->pos().y();
    if ( pos_y >= 0 && pos_y < 50 )
    {
        hover_duel_mode(); //hover决斗模式
    }
    else if ( pos_y >= 50 && pos_y < 100 )
    {
        hover_card_check(); //hover卡组整理
    }
}

void Menu::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qreal pos_y = event->pos().y();
    if ( pos_y >= 0 && pos_y < 50 )
    {
        press_duel_mode(); //press决斗模式
    }
    else if ( pos_y >= 50 && pos_y < 100 )
    {
        press_card_check(); //press卡组整理
    }
}

void Menu::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qreal pos_y = event->pos().y();
    if ( pos_y >= 0 && pos_y < 50 )
    {
        if ( id1 == 0 )
        {
            killTimer(id2);
            x = 0;
            id2 = 0;
            update();
            sourceRect.setRect(0,0,400,50);
            targetRect.setRect(0,0,400,50);
            id1 = startTimer(100);
        }
    }
    else if ( pos_y >= 50 && pos_y < 100 )
    {
        if( id2 == 0 )
        {
            killTimer(id1);
            x = 0;
            id1 = 0;
            update();
            sourceRect.setRect(0,50,400,50);
            targetRect.setRect(0,50,400,50);
            id2 = startTimer(100);
        }
    }
}

void Menu::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    pixmap = QPixmap(QString("title/menu_e_ani0.bmp"));
    sourceRect.setRect(0,0,400,250);
    targetRect.setRect(0,0,400,250);
    killTimer(id1);
    killTimer(id2);
    x = 0;
    id1 = 0;
    id2 = 0;
    update();
}


void Menu::hover_duel_mode()
{
    sourceRect.setRect(0,0,400,50);
    targetRect.setRect(0,0,400,50);
    id1 = startTimer(100);
}

void Menu::hover_card_check()
{
    sourceRect.setRect(0,50,400,50);
    targetRect.setRect(0,50,400,50);
    id2 = startTimer(100);
}

void Menu::press_duel_mode()
{
    emit duel_mode();
}

void Menu::press_card_check()
{
    emit card_check();
}

void Menu::timerEvent(QTimerEvent *)
{
    x++;
    if(x==5)
    {
        x=0;
    }
    pixmap = QPixmap(QString("title/menu_e_ani%1.bmp").arg(x));

    update();
}

void Menu::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0,0,QPixmap(QString("title/menu_e_ani0.bmp")));
    painter->drawPixmap(targetRect, pixmap, sourceRect);
}

///////////////////////////////////////

MenuScene::MenuScene()
{
    back = new Pixmap("title/title_1_e.bmp");
    menu = new Menu("title/menu_e_ani0.bmp");

    addItem(back);
    back->setPos(0, 0);
    addItem(menu);
    menu->setPos(200, 320);

    connect(menu, SIGNAL(duel_mode()), this, SIGNAL(duel_mode()));
    connect(menu, SIGNAL(card_check()), this, SIGNAL(card_check()));
}
