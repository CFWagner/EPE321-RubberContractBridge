#ifndef CARDSET_H
#define CARDSET_H

#include "card.h"

class CardSet
{
public:
    CardSet();
    void addCard(Card card);
    Card removeCard(qint8 position);
    Card getCard(qint8 position);
    qint8 getCardCount();
    void orderHand(CardSuit trumpSuit);
    void clearSet();
    void shuffle();
    void read(const QJsonObject &json);
    void write(const QJsonObject &json);
    QString toString();
private:
    QVector<Card> cards;
};

#endif // CARDSET_H
