﻿#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include "pixmap.h"
#include "dialog/button.h"

class InfoDialog : public QGraphicsObject
{
    Q_OBJECT
public:
    InfoDialog(const QString &filename);
    QPixmap pixmap;
    Button *button;
    void showAnimation();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

signals:
    void clicked();
};

#endif // INFODIALOG_H
