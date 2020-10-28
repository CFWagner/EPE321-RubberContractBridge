#ifndef CARD_H
#define CARD_H

#include "enumerations/CardSuit.h"
#include "enumerations/CardRank.h"
#include <QJsonObject>

// Represents a playing card used during bridge gameplay.
// Uniquely defined by its suit and rank
class Card
{
public:
    Card();
    Card(CardSuit suit, CardRank rank);
    CardSuit getSuit() const;
    CardRank getRank() const;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator <(const Card& card) const;
    bool operator ==(const Card& card) const;
private:
    CardSuit suit;
    CardRank rank;
};
Q_DECLARE_METATYPE(Card);

#endif // CARD_H
