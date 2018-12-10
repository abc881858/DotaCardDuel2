#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include "dialog/button.h"

class WarningDialog : public QGraphicsObject
{
    Q_OBJECT
public:
    WarningDialog(const QString &filename);
    QPixmap pixmap;
    Button *buttonYes;
    Button *buttonNo;
    void showAnimation();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

signals:
    void clicked_yes();
    void clicked_no();
};

#endif // WARNINGDIALOG_H
