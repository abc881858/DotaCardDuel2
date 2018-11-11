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

class Room : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Room(QObject* parent = nullptr);

    Pixmap *sword[10];
    Pixmap *item_shine;
    Pixmap *item_enemy_shine;

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
    int testPlace(Card::AreaFlag flag);
    void setupConnect(QList<Card *> list, bool enemy);
    void chain(int number);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void bp_clicked();
    void m2_clicked();
    void ep_clicked();

    void response_setupDeck();
    void response_startGame(QJsonObject json);
    void response_enemyStartGame();
    void response_drawPhase();
    void response_standbyPhase();
    void response_main1Phase();
    void response_endPhase();
    void response_enemySetupDeck(QJsonObject json);
    void response_enemyDrawPhase();
    void response_enemyStandbyPhase();
    void response_enemyMain1Phase();
    void response_enemyBattlePhase();
    void response_enemyMain2Phase();
    void response_enemyEndPhase();
    void response_enemyDrawFirst();
    void response_enemySpecialSummon(QJsonObject json);
    void response_enemySummon(QJsonObject json);
    void response_enemyActive(QJsonObject json);
    void response_enemySet(QJsonObject json);
    void response_enemyDeclared(QJsonObject json);
    void response_finishChain();
    void response_destroyFieldyard(QJsonObject json);
    void response_enemyDestroyFieldyard(QJsonObject json);
    void response_enemyChained(QJsonObject json);

signals:
    void hover(QString, QString);
};

#endif // ROOM_H
