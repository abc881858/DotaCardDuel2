#ifndef DECKSCENE_H
#define DECKSCENE_H

#include <QGraphicsScene>
#include "pixmap.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QGraphicsProxyWidget>

class DeckScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DeckScene(QObject* parent = 0);
    Pixmap *leftarea;
    QGraphicsProxyWidget *proxywidget;
    QListWidget *listwidget;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

signals:
    void clicked();
};

#endif // DECKSCENE_H
