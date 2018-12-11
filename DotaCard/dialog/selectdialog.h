#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include "dialog/button.h"
#include <QScrollArea>
#include <QGraphicsProxyWidget>

class SelectDialog : public QGraphicsObject
{
    Q_OBJECT
public:
    SelectDialog(const QString &filename);
    QPixmap pixmap;
    Button *button;
    void showAnimation();
    void buildDialog();
    int area{0};
    int level{0};
    QScrollArea *scrollArea;
    QGraphicsProxyWidget *proxy;
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

signals:
    void clicked_pixmap(int areaIndex, int cardIndex);
};

#endif // SELECTDIALOG_H
