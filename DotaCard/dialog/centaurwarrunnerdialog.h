#ifndef CENTAURWARRUNNERDIALOG_H
#define CENTAURWARRUNNERDIALOG_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include "button.h"

class CentaurWarrunnerDialog : public QGraphicsObject
{
    Q_OBJECT
public:
    CentaurWarrunnerDialog(const QString &filename);
    QPixmap pixmap;
    Button *button1;
    Button *button2;
    Button *button3;
    void showAnimation();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

signals:
    void clicked_button(int);
};

#endif // CENTAURWARRUNNERDIALOG_H
