#ifndef CARD_H
#define CARD_H

#include "enumerations/CardSuit.h"
#include "enumerations/CardRank.h"
#include <QJsonObject>

class Card
{
public:
    Card();
    Card(CardSuit suit, CardRank rank);
    CardSuit getSuit();
    CardRank getRank();
    void read(const QJsonObject &json);
    void write(const QJsonObject &json);
    QString toString();
private:
    CardSuit suit;
    CardRank rank;
};

#endif // CARD_H
