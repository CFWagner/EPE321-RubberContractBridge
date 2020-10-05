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
CardSuit Card::getSuit() const
{
    return suit;
}

// Getter for card rank
CardRank Card::getRank() const
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

// Overloaded < relational operator for use in sorting cards
// Cards are compared by suit first then rank according to the CardSuit and CardRank enums
bool Card::operator <(const Card& card) const
{
    if (suit == card.suit)
        return rank < card.rank;
    else
        return suit < card.suit;
}

// Overloaded == relational operator to test for card equality
// Two cards are equal if they have the same suit and rank
bool Card::operator ==(const Card& card) const
{
    return suit == card.suit && rank == card.rank;
}
