#ifndef CARDITEM_H
#define CARDITEM_H

#include "spirit.h"
#include "card.h"

class CardItem : public Spirit
{
    Q_OBJECT

public:
    explicit CardItem(Card *card);

    enum PlaceFlag
    {
        No_Place,
        Deck_Place,
        Hand_Place,
        Front_Place,
        Back_Place,
        Grave_Place,
        Remote_Deck_Place,
        Remote_Hand_Place,
        Remote_Front_Place,
        Remote_Back_Place,
        Remote_Grave_Place
    };

    void changeImage();
    QString getFileNameLarge();
    QString getFileNameMedium();
    QString getFileNameSmall();

    CardItem::PlaceFlag getPlace() const;
    void setPlace(CardItem::PlaceFlag place);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *widget);

private:
    Card *m_card;

    PlaceFlag m_place{No_Place};

    QPixmap lighterPixmap;
    QPixmap originalPixmap;
    QImage frameImage;

signals:
    void hoverLeave();
    void mousePress();
    void update_big_image(QString);
};

#endif // CARDITEM_H
