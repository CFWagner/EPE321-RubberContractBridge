#ifndef CARDSET_H
#define CARDSET_H
#include "card.h"

// Represents any collection of cards that occurs during the bridge game
// For example, deck, hand and trick are all card sets
class CardSet
{
public:
    CardSet();
    void addCard(Card card);
    Card removeCard(qint8 position);
    Card removeTopCard();
    Card getCard(qint8 position) const;
    bool containsCard(const Card &card) const;
    bool containsSuit(CardSuit suit) const;
    qint8 getCardCount() const;
    void orderHand();
    void clearSet();
    void shuffle();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const CardSet& cardSet) const;
private:
    QVector<Card> cards;
};
#endif // CARDSET_H
