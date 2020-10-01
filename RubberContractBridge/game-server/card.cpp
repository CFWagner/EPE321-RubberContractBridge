#include "card.h"

// Default constructor
Card::Card() {}

// Constructor using card rank and suit
Card::Card(CardSuit suit, CardRank rank)
{
    this->suit = suit;
    this->rank = rank;
}

// Getter for card suit
CardSuit Card::getSuit()
{
    return suit;
}

// Getter for card rank
CardRank Card::getRank()
{
    return rank;
}

// Initialize card attributes from JSON object
void Card::read(const QJsonObject &json)
{
    suit = CardSuit(json["suit"].toInt());
    rank = CardRank(json["rank"].toInt());
}

// Add Card instance attributes to the JSON object argument
void Card::write(QJsonObject &json) const
{
    json["suit"] = suit;
    json["rank"] = rank;
}
