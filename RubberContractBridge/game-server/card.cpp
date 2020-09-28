#include "card.h"

Card::Card() {}

Card::Card(CardSuit suit, CardRank rank)
{
    this->suit = suit;
    this->rank = rank;
}

CardSuit Card::getSuit()
{
    return suit;
}

CardRank Card::getRank()
{
    return rank;
}

void Card::read(const QJsonObject &json)
{
    suit = CardSuit(qRound(json["suit"].toDouble()));
    rank = CardRank(qRound(json["rank"].toDouble()));
}

void Card::write(const QJsonObject &json)
{
    json["suit"] = suit;
    json["rank"] = rank;
}
