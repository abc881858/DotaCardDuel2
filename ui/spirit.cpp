#include "spirit.h"

Spirit::Spirit(const QString &filename)
    : pixmap(filename)
{
//    if(center_as_origin)
//    {
//        setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
//    }
}

QRectF Spirit::boundingRect() const
{
    return QRectF{0, 0, qreal(pixmap.width()), qreal(pixmap.height())};
}

void Spirit::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, pixmap);
}

void Spirit::setPixmap(const QString& filename)
{
    pixmap.load(filename);
}

QPixmap Spirit::getPixmap() const
{
    return pixmap;
}
