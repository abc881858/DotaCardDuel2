#include "dota.h"
#include "engine.h"
#include "net.h"
#include <QMessageBox>
#include <utility>

Q_GLOBAL_STATIC(Dota, dota)

Dota* Dota::instance()
{
    return dota();
}

void Dota::initialize()
{
    qNet->initialize();
    connect(qNet, &Net::request_moveCard, this, &Dota::response_moveCard);

    connect(qNet, SIGNAL(request_enemyBeEquiped(QJsonObject)), this, SLOT(response_enemyBeEquiped(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyBeAttack(QJsonObject)), this, SLOT(response_enemyBeAttack(QJsonObject)));
    connect(qNet, SIGNAL(request_finishChain()), this, SLOT(response_finishChain()));
    connect(qNet, SIGNAL(request_enemyChained(QJsonObject)), this, SLOT(response_enemyChained(QJsonObject)));
    connect(qNet, SIGNAL(request_setupDeck()), this, SLOT(response_setupDeck()));
    connect(qNet, SIGNAL(request_enemySetupDeck(QJsonObject)), this, SLOT(response_enemySetupDeck(QJsonObject)));
    connect(qNet, SIGNAL(request_startGame(QJsonObject)), this, SLOT(response_startGame(QJsonObject)));
    connect(qNet, SIGNAL(request_enemyStartGame()), this, SLOT(response_enemyStartGame()));
    connect(qNet, SIGNAL(request_drawPhase()), this, SLOT(response_drawPhase()));
    connect(qNet, SIGNAL(request_standbyPhase()), this, SLOT(response_standbyPhase()));
    connect(qNet, SIGNAL(request_main1Phase()), this, SLOT(response_main1Phase()));
    connect(qNet, SIGNAL(request_endPhase()), this, SLOT(response_endPhase()));
    connect(qNet, SIGNAL(request_enemyDrawPhase()), this, SLOT(response_enemyDrawPhase()));
    connect(qNet, SIGNAL(request_enemyStandbyPhase()), this, SLOT(response_enemyStandbyPhase()));
    connect(qNet, SIGNAL(request_enemyMain1Phase()), this, SLOT(response_enemyMain1Phase()));
    connect(qNet, SIGNAL(request_enemyBattlePhase()), this, SLOT(response_enemyBattlePhase()));
    connect(qNet, SIGNAL(request_enemyMain2Phase()), this, SLOT(response_enemyMain2Phase()));
    connect(qNet, SIGNAL(request_enemyEndPhase()), this, SLOT(response_enemyEndPhase()));

    phase = No_Phase;
    whoIsDoing = true;

    oneTurnOneNormalSummon = false; //一回合一次普通召唤
    firstTurn = true;

    attackSourceCard = nullptr;
    attackDestinationCard = nullptr;
    equipSpellCard = nullptr;
    equipMonsterCard = nullptr;

    authenticateCardAreaList.clear(); //初始化鉴权
    authenticateCardActive = false;

    for(int i = 0; i < 5; ++i)
    {
        fieldyardCards[i] = nullptr;
        fieldgroundCards[i] = nullptr;
        enemyFieldyardCards[i] = nullptr;
        enemyFieldgroundCards[i] = nullptr;
    }
}

void Dota::setSearchReason(Dota::ReasonFlag flag)
{
    searchReason = flag;

    if(flag == Dota::No_Reason)
    {
        authenticateCardAreaList.clear();
        authenticateCardActive = false; //不再寻找攻击目标
    }
    else if(flag==Dota::BeAttacked_Reason)
    {
        addAuthenticateCardArea(Card::EnemyFieldyard_Area);
    }
    else if(flag==Dota::ChainDeclared_Reason)
    {
        addAuthenticateCardArea(Card::Fieldyard_Area);
        addAuthenticateCardArea(Card::Fieldground_Area);
        needAuthenticateCardActive();
    }
    else if(flag==Dota::BeEquiped_Reason)
    {
        addAuthenticateCardArea(Card::Fieldyard_Area);
    }
}

Dota::ReasonFlag Dota::getSearchReason()
{
    return searchReason;
}

bool Dota::isSearchingTargetCard()
{
    if(!authenticateCardAreaList.isEmpty())
    {
        return true;
    }
//    一般 target 都有 area，可以以小见大,窥一斑而知全豹
//    if(authenticateCardActive)
//    {
//        return true;
//    }
    return false; //全部 authenticate 都不 need
}

void Dota::addAuthenticateCardArea(Card::AreaFlag flag)
{
    authenticateCardAreaList << flag;
}

void Dota::needAuthenticateCardActive()
{
    authenticateCardActive = true;
}

bool Dota::authenticateCard(Card *card)
{
    if(!authenticateCardAreaList.isEmpty())
    {
        if(!authenticateCardAreaList.contains(card->getArea()))
        {
            return false;
        }
    }
    if(authenticateCardActive)
    {
        if(card->getArea() == Card::Fieldyard_Area)
        {
            if(card->testEffectFromFieldyard())
            {
                return false;
            }
        }
        else if(card->getArea() == Card::Fieldground_Area)
        {
            if(!card->testEffectFromFieldground())
            {
                return false;
            }
        }
    }
    return true; //全部都鉴权成功，return true
}

Card* Dota::getCardFromIndex(int index)
{
    return deckCards.at(index);
}

Card* Dota::getEnemyCardFromIndex(int index)
{
    return enemyDeckCards.at(index);
}

int Dota::getCardIndex(Card* card)
{
    Card::AreaFlag flag = card->getArea();

    if(flag == Card::Hand_Area)
    {
        if(card != nullptr)
        {
            return handCards.indexOf(card);
        }
    }
    else if(flag == Card::Fieldyard_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(fieldyardCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::EnemyFieldyard_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(enemyFieldyardCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::Fieldground_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(fieldgroundCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    else if(flag == Card::EnemyFieldground_Area)
    {
        if(card != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if(enemyFieldgroundCards[i] == card)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

//////////////////////
bool Dota::hasMonster()
{
    for(auto & fieldyardCard : fieldyardCards)
    {
        if(fieldyardCard != nullptr)
        {
            return true;
        }
    }
    return false;
}

bool Dota::hasEnemyMonster()
{
    for(auto & enemyFieldyardCard : enemyFieldyardCards)
    {
        if(enemyFieldyardCard != nullptr)
        {
            return true;
        }
    }
    return false;
}

bool Dota::hasEmptyBackSlot()
{
    for(auto & fieldgroundCard : fieldgroundCards)
    {
        if(fieldgroundCard == nullptr)
        {
            return true;
        }
    }
    return false;
}

bool Dota::hasEmptyFrontSlot()
{
    for(auto & fieldyardCard : fieldyardCards)
    {
        if(fieldyardCard == nullptr)
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////

int Dota::testPlace(Card::AreaFlag flag)
{
    for(int i = 0; i < 5; ++i)
    {
        if(flag == Card::Fieldyard_Area)
        {
            if(fieldyardCards[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::Fieldground_Area)
        {
            if(fieldgroundCards[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::EnemyFieldyard_Area)
        {
            if(enemyFieldyardCards[i] == nullptr)
            {
                return i;
            }
        }
        else if(flag == Card::EnemyFieldground_Area)
        {
            if(enemyFieldgroundCards[i] == nullptr)
            {
                return i;
            }
        }
    }
    return -1;
}

void Dota::activeSpellCard(Card *card)
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldground_Area;
    move.indexFrom = getCardIndex(card);
    move.indexTo = testPlace(Card::Fieldground_Area);
    move.reason = CardMoveStruct::REASON_activeSpellCard;
    moveCard(move);

    emit showChainAnimation(move.indexTo, Card::Fieldground_Area);
//    qNet->sendChained(move.indexTo, Card::Fieldground_Area); // 考虑下提前发送Net连锁动画

    if(card->getKind() == Card::EquipSpell_Kind)
    {
        //先到场地，发光，弹出对话框，点确定，选择卡，装备卡动画
        if(QMessageBox::information(nullptr, "title", "please select one monster to equip.", QMessageBox::Yes))
        {
            qDebug() << "selectOneMonsterToEquip";
        }
        equipSpellCard = card;
        setSearchReason(Dota::BeEquiped_Reason);
    }
}

void Dota::beEquiped()
{
    //动画
    //chain's monster == pressCard
    //qNet equip
    equipSpellCard->equipMonsterCard = equipMonsterCard;
    equipMonsterCard->equipSpellCards << equipSpellCard;

    qNet->sendBeEquiped(getCardIndex(equipSpellCard), getCardIndex(equipMonsterCard));

    equipSpellCard = nullptr;
    equipMonsterCard = nullptr;
}

void Dota::response_enemyBeEquiped(QJsonObject json)
{
    //装备卡牌的动画
    int equipSpellCardIndex = json["equipSpellCardIndex"].toInt();
    int equipMonsterCardIndex = json["equipMonsterCardIndex"].toInt();
    equipSpellCard = enemyFieldgroundCards[equipSpellCardIndex];
    equipMonsterCard = enemyFieldyardCards[equipMonsterCardIndex];
    equipSpellCard->equipMonsterCard = equipMonsterCard;
    equipMonsterCard->equipSpellCards << equipSpellCard;
    equipSpellCard = nullptr;
    equipMonsterCard = nullptr;
}

void Dota::specialSummonCard(Card *card)
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = getCardIndex(card);
    move.indexTo = testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_specialSummonCard;
    moveCard(move);
}
void Dota::summonCard(Card *card)
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = getCardIndex(card);
    move.indexTo = testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_summonCard;
    moveCard(move);
}
void Dota::setCard(Card *card)
{
    CardMoveStruct move;
    move.areaFrom = Card::Hand_Area;
    move.areaTo = Card::Fieldyard_Area;
    move.indexFrom = getCardIndex(card);
    move.indexTo = testPlace(Card::Fieldyard_Area);
    move.reason = CardMoveStruct::REASON_setCard;
    moveCard(move);
}
void Dota::moveCard(CardMoveStruct move)
{
    Card *card = nullptr;
    int indexFrom = move.indexFrom;
    int indexTo = move.indexTo;

    switch (move.areaFrom)
    {
    case Card::Deck_Area:
        card = deckCards.takeAt(indexFrom);
        break;
    case Card::Hand_Area:
        card = handCards.takeAt(indexFrom);
        break;
    case Card::Fieldyard_Area:
        card = fieldyardCards[indexFrom];
        fieldyardCards[indexFrom] = nullptr;
        break;
    case Card::Fieldground_Area:
        card = fieldgroundCards[indexFrom];
        fieldgroundCards[indexFrom] = nullptr;
        break;
    case Card::Graveyard_Area:
        card = graveyardCards.takeAt(indexFrom);
        break;

    case Card::EnemyDeck_Area:
        card = enemyDeckCards.takeAt(indexFrom);
        break;
    case Card::EnemyHand_Area:
        card = enemyHandCards.takeAt(indexFrom);
        break;
    case Card::EnemyFieldyard_Area:
        card = enemyFieldyardCards[indexFrom];
        enemyFieldyardCards[indexFrom] = nullptr;
        break;
    case Card::EnemyFieldground_Area:
        card = enemyFieldgroundCards[indexFrom];
        enemyFieldgroundCards[indexFrom] = nullptr;
        break;
    case Card::EnemyGraveyard_Area:
        card = enemyGraveyardCards.takeAt(indexFrom);
        break;
    default:
        // for No_Area
        break;
    }

    switch (move.areaTo)
    {
    case Card::Deck_Area:
        deckCards << card;
        break;
    case Card::Hand_Area:
        handCards << card;
        break;
    case Card::Fieldyard_Area:
        fieldyardCards[indexTo] = card;
        break;
    case Card::Fieldground_Area:
        fieldgroundCards[indexTo] = card;
        break;
    case Card::Graveyard_Area:
        graveyardCards << card;
        break;

    case Card::EnemyDeck_Area:
        enemyDeckCards << card;
        break;
    case Card::EnemyHand_Area:
        enemyHandCards << card;
        break;
    case Card::EnemyFieldyard_Area:
        enemyFieldyardCards[indexTo] = card;
        break;
    case Card::EnemyFieldground_Area:
        enemyFieldgroundCards[indexTo] = card;
        break;
    case Card::EnemyGraveyard_Area:
        enemyGraveyardCards << card;
        break;
    default:
        // for No_Area
        break;
    }

    if(move.reason == CardMoveStruct::REASON_setupCard)
    {
        card->setupCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemySetupCard)
    {
        card->enemySetupCard();
    }
    else if(move.reason == CardMoveStruct::REASON_drawCard)
    {
        card->drawCard();
        qNet->moveCard(move.toJson()); // ToDo: 改为 emit 到 qNet
    }
    else if(move.reason == CardMoveStruct::REASON_enemyDrawCard)
    {
        card->enemyDrawCard();
    }
    else if(move.reason == CardMoveStruct::REASON_specialSummonCard)
    {
        card->specialSummonCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemySpecialSummonCard)
    {
        card->enemySpecialSummonCard();
    }
    else if(move.reason == CardMoveStruct::REASON_summonCard)
    {
        card->summonCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemySummonCard)
    {
        card->enemySummonCard();
    }
    else if(move.reason == CardMoveStruct::REASON_activeSpellCard)
    {
        card->activeCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemyActiveCard)
    {
        card->enemyActiveCard();
    }
    else if(move.reason == CardMoveStruct::REASON_setCard)
    {
        card->setCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemySetCard)
    {
        card->enemySetCard();
    }
    else if(move.reason == CardMoveStruct::REASON_destroyCard)
    {
        card->destroyCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemyDestroyCard)
    {
        card->enemyDestroyCard();
    }
    else if(move.reason == CardMoveStruct::REASON_destroyEnemyCard)
    {
        card->enemyDestroyCard();
        qNet->moveCard(move.toJson());
    }
    else if(move.reason == CardMoveStruct::REASON_enemyDestroyEnemyCard)
    {
        card->destroyCard();
    }
    else
    {
        // reason == CardMoveStruct::REASON_unknown
    }

    emit moveCardItem(move);
}
void Dota::response_moveCard(QJsonObject json)
{
    CardMoveStruct move = CardMoveStruct::fromJson(std::move(json));
    moveCard(move);
}


//不连锁之后，发动卡牌效果一方执行连锁。
void Dota::response_finishChain()
{
    if(chainStack.isEmpty())
    {
        return;
    }
    Dota::ReasonFlag flag = chainStack.pop();

    if(flag == Dota::ChainDeclared_Reason) // 这里应该有个while循环，response_finishChain();
    {
        chainCard->active();
        chainCard = nullptr;
    }
    else if(flag == Dota::BeAttacked_Reason)
    {
        //解锁中，不响应
        //先问自己是否连锁，再问对方是否连锁 /*简单处理下攻击后的伤亡情况*/

        if(attackDestinationCard->getStand())
        {
            if(attackSourceCard->getATK() <= attackDestinationCard->getATK())
            {
                CardMoveStruct move;
                move.areaFrom = Card::Fieldyard_Area;
                move.areaTo = Card::Graveyard_Area;
                move.indexFrom = getCardIndex(attackSourceCard);
                move.indexTo = -1;
                move.reason = CardMoveStruct::REASON_destroyCard;
                moveCard(move);
                if(attackSourceCard->getKind()==Card::EffectMonster_Kind && !attackSourceCard->equipSpellCards.isEmpty())
                {
                    for(Card* spell : attackSourceCard->equipSpellCards)
                    {
                        if(spell->getArea() == Card::Fieldground_Area)
                        {
                            CardMoveStruct move;
                            move.areaFrom = Card::Fieldground_Area;
                            move.areaTo = Card::Graveyard_Area;
                            move.indexFrom = getCardIndex(spell);
                            move.indexTo = -1;
                            move.reason = CardMoveStruct::REASON_destroyCard;
                            moveCard(move);
                        }
                    }
                }
            }
        }

        if(attackSourceCard->getStand())
        {
            if(attackDestinationCard->getATK() <= attackSourceCard->getATK())
            {
                CardMoveStruct move;
                move.areaFrom = Card::EnemyFieldyard_Area;
                move.areaTo = Card::EnemyGraveyard_Area;
                move.indexFrom = getCardIndex(attackDestinationCard);
                move.indexTo = -1;
                move.reason = CardMoveStruct::REASON_destroyEnemyCard;
                moveCard(move);
                if(attackDestinationCard->getKind()==Card::EffectMonster_Kind && !attackDestinationCard->equipSpellCards.isEmpty())
                {
                    for(Card* spell : attackDestinationCard->equipSpellCards)
                    {
                        if(spell->getArea() == Card::EnemyFieldground_Area)
                        {
                            CardMoveStruct move;
                            move.areaFrom = Card::EnemyFieldground_Area;
                            move.areaTo = Card::EnemyGraveyard_Area;
                            move.indexFrom = getCardIndex(spell);
                            move.indexTo = -1;
                            move.reason = CardMoveStruct::REASON_destroyEnemyCard;
                            moveCard(move);
                        }
                    }
                }
            }

        }

        attackSourceCard = nullptr;
        attackDestinationCard = nullptr;
        whoIsDoing = true;
    }

    qNet->sendFinishChain(); //考虑下 最后一下可以不发

}

///////////////////////
///////////////////////
///////////////////////
///////////////////////

void Dota::attack(Card* card)
{
    attackSourceCard = card;
    if(hasEnemyMonster())
    {
        setSearchReason(Dota::BeAttacked_Reason);
    }
    else
    {
        attackSourceCard->canAttack = false;
        beAttacked();
    }
}

void Dota::beAttacked()
{
    //我方已经发动了战斗宣言。
    //发动卡片的效果吗？
    //You(Your opponent) have declared battle.
    //Activate the effect of a card?
//    whoIsDoing = false; //什么都不能做，等待对方回应

//    bool can_chain = false;
//    bool will_chain = false;
//    for(int i=0; i<5; i++)
//    {
//        if(fieldyardCards[i]!=nullptr) //适用于对方战斗场合也能发动的怪兽效果
//        {
//            if(fieldyardCards[i]->testEffectFromFieldyard() > 0)
//            {
//                can_chain = true;
//                break;
//            }
//        }
//        if(fieldgroundCards[i]!=nullptr)
//        {
//            if(fieldgroundCards[i]->testEffectFromFieldground())
//            {
//                can_chain = true;
//                break;
//            }
//        }
//    }

//    if(can_chain) //如果能连锁，请问你连不连锁
//    {
//        //“对方”已经发动了“战斗宣言”。“发动”卡片的效果吗？
//        if(QMessageBox::Yes == QMessageBox::question(nullptr, "",
//                                 QString(tr("Your opponent has declared battle.Activate the effect of a card")),
//                                 QMessageBox::Yes, QMessageBox::No))
//        {
//            whoIsDoing = true;
//            will_chain = true;

//            //只有确认连锁了，才需要指定连锁目标的类型
//            setSearchReason(Dota::ChainDeclared_Reason);
//            //还没选target就已经想好了原因，是连锁对方战斗宣言的
//        }
//    }

//    if(!will_chain) //如果你不连锁，就告诉对方我不连锁
//    {
//        whoIsDoing = false;
//        qNet->sendFinishChain();
//    }

    //无论表侧里侧，都可以选择作为目标target
    int sourceIndex = getCardIndex(attackSourceCard); //主动攻击方
    int targetIndex = -1;

    if(hasEnemyMonster())
    {
        targetIndex = getCardIndex(attackDestinationCard); //被攻击方
    }

    emit showAttackAnimation(sourceIndex, targetIndex);

    whoIsDoing = false;
    qNet->sendBeAttacked(sourceIndex, targetIndex);
}

void Dota::response_enemyBeAttack(QJsonObject json)
{
    int sourceIndex = json["sourceIndex"].toInt();
    int targetIndex = json["targetIndex"].toInt();

    attackSourceCard = enemyFieldyardCards[sourceIndex];
    attackDestinationCard = nullptr;

    if(targetIndex != -1)
    {
        attackDestinationCard = fieldyardCards[targetIndex];
    }

    emit showEnemyAttackAnimation(sourceIndex, targetIndex);

    qNet->sendFinishChain(); //目前没处理
}

void Dota::chainDeclared()
{
    whoIsDoing = false; //????

    int targetIndex = getCardIndex(chainCard);
    int areaIndex = chainCard->getArea();

    emit showChainAnimation(targetIndex, areaIndex);

    qNet->sendChained(targetIndex, areaIndex); // 考虑下提前发送Net连锁动画
}

void Dota::chain(int number)
{
    bool can_do = false;
    for(auto & fieldgroundCard : fieldgroundCards)
    {
//        if(myFieldyard[i]!=NULL)
//        {
//            if(myFieldyard[i]->testEffectFromFieldyard())
//            {
//                can_do = true;
//                break;
//            }
//        }
        if(fieldgroundCard!=nullptr)
        {
            if(fieldgroundCard->testEffectFromFieldground())
            {
                can_do = true;
                break;
            }
        }
    }

    if(can_do)
    {
        if(QMessageBox::question(nullptr, QString(tr("Warning")), QString(tr("Active Effect")), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            whoIsDoing = true;
            return;
        }
    }

    qNet->sendMessage(number);
}

void Dota::response_enemyChained(QJsonObject json)
{
    qDebug() << "response_enemyChained";
    int targetIndex = json["targetIndex"].toInt();
    int areaIndex = json["areaIndex"].toInt();

//    CardItem *item = nullptr;
//    if(areaIndex == Card::Fieldyard_Area)
//    {
//        item = enemyFieldyardItems[targetIndex];
//    }
//    else if(areaIndex == Card::Fieldground_Area)
//    {
//        item = enemyFieldgroundItems[targetIndex];
//    }

//    item_enemy_shine->setPos(item->pos() - QPoint(12,-1));
//    item_enemy_shine->doShineAnimation();

    emit showChainAnimation(targetIndex, areaIndex);
}

///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

void Dota::response_setupDeck()
{
    QVariantList allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QVariant(ISDN);
        Card* card = Engine::instance()->cloneCard(ISDN);
        deckCards << card;
        emit createCardItem(deckCards.size()-1);
    }
    file.close();

    qNet->sendDeck(allISDN); //2000
}

void Dota::response_enemySetupDeck(QJsonObject json)
{
    //先设置对方卡组
    QJsonArray array = json["array"].toArray();
    QVariantList list = array.toVariantList();
    for(const QVariant& value : list)
    {
        int ISDN = value.toInt();
        Card* card = Engine::instance()->cloneCard(ISDN);
        enemyDeckCards << card;
        emit createEnemyCardItem(enemyDeckCards.size()-1);
    }

    //再设置自己卡组
    QVariantList allISDN;
    QFile file("test1.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);
    while (!text_stream.atEnd())
    {
        int ISDN = text_stream.readLine().toInt();
        allISDN << QVariant(ISDN);
        Card* card = Engine::instance()->cloneCard(ISDN);
        deckCards << card;
        emit createCardItem(deckCards.size()-1);
    }
    file.close();

    qNet->sendEnemyDeck(allISDN); //2001
}

void Dota::response_startGame(QJsonObject json)
{
    //先设置对方卡组
    QJsonArray array = json["array"].toArray();
    QVariantList list = array.toVariantList();
    for(const QVariant& value : list)
    {
        int ISDN = value.toInt();
        Card* card = Engine::instance()->cloneCard(ISDN);
        enemyDeckCards << card;
        emit createEnemyCardItem(enemyDeckCards.size()-1);
    }

    emit goStartGame();
}

void Dota::response_enemyStartGame()
{
    emit goStartGame();
}

void Dota::goStartPhase()
{
    for (int i = 0; i < 5; ++i)
    {
        qDebug() << "draw a card";

        CardMoveStruct move;
        move.areaFrom = Card::Deck_Area;
        move.areaTo = Card::Hand_Area;
        move.indexFrom = 0;
        move.indexTo = -1; // 代表默认，加入到手牌末尾
        move.reason = CardMoveStruct::REASON_drawCard;
        moveCard(move);
    }

    qNet->sendMessage(3000);
}

void Dota::response_drawPhase()
{
    CardMoveStruct move;
    move.areaFrom = Card::Deck_Area;
    move.areaTo = Card::Hand_Area;
    move.indexFrom = 0;
    move.indexTo = -1; // 代表默认，加入到手牌末尾
    move.reason = CardMoveStruct::REASON_drawCard;
    moveCard(move);

    phase = Dota::Draw_Phase;
    qNet->sendMessage(10001);

//    emit goDrawPhase();
}

void Dota::response_enemyDrawPhase() //client0收到client1说它进入了抽卡流程
{
    phase = Dota::EnemyDraw_Phase;
    //也要把对方的手牌显示出来

    //本来是蓝色EP在闪动
    //让我丢弃手牌
    //对方玩家回合蓝色渐变到红色，全部变成红色phase动画
    //红色DP在闪动
    //中间渐入渐出红色抽卡流程
    //弹出对话框问“进入对方的回合。发动卡片的效果吗？”
    chain(10002);
}

void Dota::response_standbyPhase()
{
    oneTurnOneNormalSummon = true;
    for (int i=0;i<5;i++) //遍历所有卡牌，确保一回合一次，不会因为area变化而多次选发
    {
        if(fieldyardCards[i]!=nullptr)
        {
            fieldyardCards[i]->standby();
        }
        if(fieldgroundCards[i]!=nullptr)
        {
            fieldgroundCards[i]->standby();
        }
    }

    phase = Dota::Standby_Phase;
    qNet->sendMessage(20001);

    emit goStandbyPhase();
}

void Dota::response_enemyStandbyPhase()
{
    phase = Dota::EnemyStandby_Phase;
    //初始化对方卡牌的standby函数

    //红色SP闪动
    //显示红色准备流程淡入淡出动画

    whoIsDoing = false;;
    qNet->sendMessage(20002);
}

void Dota::response_main1Phase()
{
    whoIsDoing = true;
    //    //进入主要流程需要刷新鼠标手指样式
    //    for(Card* card : myHand)
    //    {
    //        card->changeFinger();
    //    }
    //    //我方进入主要流程，对方没有连锁点

    phase = Dota::Main1_Phase;
    qNet->sendMessage(30001);

    emit goMain1Phase();
}

void Dota::response_enemyMain1Phase()
{
    phase = Dota::EnemyMain1_Phase;
    whoIsDoing = false;;
    //红色M1闪动
    //显示红色主要流程1淡入淡出动画
}

void Dota::tryGoBattlePhase()
{
    if(isSearchingTargetCard())
    {
        return;
    }
    if (phase == Dota::Main1_Phase)
    {
        whoIsDoing = true;
        //我方进入战斗流程，对方没有连锁点

        QList<int> list;
        for (int i = 0; i<5; i++)
        {
            if(fieldyardCards[i] != nullptr)
            {
                if(fieldyardCards[i]->getFace() && fieldyardCards[i]->getStand())
                {
                    list << i;
                }
            }
        }
        emit goBattlePhase(list);

        phase = Dota::Battle_Phase;
        qNet->sendMessage(40001);
    }
}

void Dota::response_enemyBattlePhase()
{
    whoIsDoing = false;;
    phase = Dota::EnemyBattle_Phase;

    //显示宝剑
    QList<int> list;
    for (int i = 0; i < 5; i++)
    {
        if(enemyFieldyardCards[i] != nullptr)
        {
            if(enemyFieldyardCards[i]->getFace() && enemyFieldyardCards[i]->getStand())
            {
                list << (i+5);
            }
        }
    }
    emit goBattlePhase(list);
}

void Dota::tryGoMain2Phase()
{
    if(isSearchingTargetCard())
    {
        return;
    }
    if (phase == Dota::Battle_Phase)
    {
        whoIsDoing = true;
        //我方进入战斗流程，对方没有连锁点

        emit goMain2Phase();

        phase = Dota::Main2_Phase;
        qNet->sendMessage(50001);
    }
}

void Dota::response_enemyMain2Phase()
{
    whoIsDoing = false;
    phase = Dota::EnemyMain2_Phase;

    emit goMain2Phase(); //TODO: 这里还是用的蓝色动画

    //红色M2闪动
    //显示红色主要流程2淡入淡出动画
}

void Dota::tryGoEndPhase()
{
    if(isSearchingTargetCard())
    {
        return;
    }
    if (phase == Dota::Main1_Phase
        || phase == Dota::Battle_Phase
        || phase == Dota::Main2_Phase)
    {
        whoIsDoing = false;
        //我方进入结束流程，对方有连锁点

        emit goEndPhase();

        phase = Dota::MyEnd_Phase;
        qNet->sendMessage(60001);
    }
}

void Dota::response_endPhase()
{
    //隐藏对方行动字样
//    whoIsDoing = true;
//    DisCard from your hand. [NULL_mini] 手牌上限6张

    whoIsDoing = false;
    qNet->sendMessage(70001);
}

void Dota::response_enemyEndPhase() //client1收到client0问是否连锁
{
    phase = Dota::EnemyEnd_Phase;

    emit goEndPhase();

    //本来是红色M2在闪动
    //上面显示蓝色对方行动

    //红色EP闪动
    //显示红色结束流程渐入渐出动画
    //弹出对话框问“对方将要结束回合。发动卡片的效果吗？”

    chain(60002);
}
