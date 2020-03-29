#ifndef SPIRIT_H
#define SPIRIT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>

class Spirit : public QGraphicsObject
{
    Q_OBJECT

public:
    Spirit(const QString &filename);
    //bool center_as_origin = true
    void setPixmap(const QString& filename);
    QPixmap getPixmap() const;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF boundingRect() const;

private:
    QPixmap pixmap;
};

#endif // SPIRIT_H
