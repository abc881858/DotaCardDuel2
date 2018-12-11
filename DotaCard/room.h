#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include <QPixmap>
#include "phase.h"
#include "pixmap.h"
#include "carditem.h"
#include <QJsonArray>
#include <QJsonObject>
#include "structs.h"
#include "dialog/infodialog.h"
#include "dialog/warningdialog.h"
#include "dialog/selectdialog.h"

class Room : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Room(QObject* parent = nullptr);

    Pixmap *sword[10];
    Pixmap *equipFieldyard[10];
    Pixmap *equipFieldground[10];
    Pixmap *item_shine;
//    Pixmap *item_enemy_shine;
    InfoDialog *dialog;
    WarningDialog *dialog2;
    SelectDialog *dialog3;

//    QGraphicsTextItem word[10];
//    GraphicsPixmapObject* duifangxingdong;
    Pixmap* bp_pix;

    Pixmap *leftarea;
    Pixmap *rightarea;
    Pixmap *bigImage;
    QGraphicsProxyWidget *textwidget;
    QTextEdit *textedit;

    Pixmap *juedoukaishi;

    Phase *dp;
    Phase *sp;
    Phase *m1;
    Phase *bp;
    Phase *m2;
    Phase *ep;

    Pixmap *dp_pix;
    Pixmap *sp_pix;
    Pixmap *m1_pix;
    Pixmap *m2_pix;
    Pixmap *ep_pix;

//    QGraphicsPixmapItem mySmallFrame;
//    QGraphicsPixmapItem yourSmallFrame;
//    CardItem* activeEffectCard;
//    Card* enemyTakedCard;

    QList<CardItem*> handItems;
    QList<CardItem*> deckItems;
    CardItem* fieldyardItems[5];
    CardItem* fieldgroundItems[5];
    QList<CardItem*> graveyardItems;
    QList<CardItem*> enemyDeckItems;
    QList<CardItem*> enemyHandItems;
    CardItem* enemyFieldyardItems[5];
    CardItem* enemyFieldgroundItems[5];
    QList<CardItem*> enemyGraveyardItems;

    void adjustHandItems();
    void adjustEnemyHandItems();
    void chain(int number);

    void hideSwords();

    CardItem* getCardItemFromIndex(int targetIndex, int areaIndex);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void moveCardItem(CardMoveStruct);
    void goBattlePhase(QList<int> list);
    void goMain2Phase();
    void goEndPhase();
    void goDrawPhase();
    void goStartGame();
    void goStandbyPhase();
    void goMain1Phase();

    void createCardItem(int index);
    void createEnemyCardItem(int index);

    void hoverEnter();
//    void hoverLeave();
//    void mousePress();

    void showAttackAnimation(int sourceIndex, int targetIndex);
    void showChainAnimation(int targetIndex, int areaIndex);
    void showEnemyAttackAnimation(int sourceIndex, int targetIndex);
    void showEquipAnimation(int from, int to);
    void showEquipHoverAnimation(int targetIndex, int areaIndex);
    void hideEquipHoverAnimation(int targetIndex, int areaIndex);
    void showInfoDialog();
    void showWarningDialog();
    void showSelectDialog();
};

#endif // ROOM_H
