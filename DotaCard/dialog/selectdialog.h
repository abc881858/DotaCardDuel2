#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include "button.h"
#include <QScrollArea>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>

class SelectDialog : public QGraphicsObject
{
    Q_OBJECT
public:
    SelectDialog(const QString &filename);
    QPixmap pixmap;
    void showAnimation();
    void buildDialog();
    int area{0};
    int level{0};
    QScrollArea *scrollArea;
    QHBoxLayout *layout;
    QGraphicsProxyWidget *proxy;
    QWidget *widget;
    int i{-1};
    int j{-1};
public slots:
    void hideAnimation();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

signals:
    void selected(int cardIndex);
};

#endif // SELECTDIALOG_H
