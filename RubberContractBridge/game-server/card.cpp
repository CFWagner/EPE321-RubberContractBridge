#include "card.h"

Card::Card()
{

}

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

}

void Card::write(const QJsonObject &json)
{

}

QString Card::toString()
{
    return "";
}
