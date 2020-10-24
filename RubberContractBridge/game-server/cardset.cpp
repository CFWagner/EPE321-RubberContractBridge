#include "cardset.h"
#include <algorithm>
#include <QJsonArray>

// Default constructor
CardSet::CardSet() {}

// Add card to the bottom of the set. The top of the set is located at index 0
void CardSet::addCard(Card card)
{
    cards.append(card);
}

// Return and remove card at given position from set. The top of the set is located at index 0
Card CardSet::removeCard(qint8 position)
{
    return cards.takeAt(position);
}

// Return and remove card at index 0 in the card set
Card CardSet::removeTopCard()
{
    return cards.takeAt(0);
}

// Return and remove card at given position from set. The top of the set is located at index 0
Card CardSet::getCard(qint8 position) const
{
    return cards.value(position);
}

// Check if the set of cards contains the specified card
bool CardSet::containsCard(const Card &card) const
{
    return cards.contains(card);
}

// Check if the set of cards contains at least one card with the specified suit
bool CardSet::containsSuit(CardSuit suit) const
{
    for(const Card &card: cards){
        if(card.getSuit() == suit)
            return true;
    }
    return false;
}

// Getter for number of cards currently in the card set
qint8 CardSet::getCardCount() const
{
    return cards.count();
}

// Orders card set by suit then rank using the precedence defined in the CardSuit and CardRank enums
// Lower precedence cards (lower enum values) are placed at the top (index 0) and vice versa
void CardSet::orderHand()
{
    std::sort(cards.begin(), cards.end());
}

// Remove all cards from the set
void CardSet::clearSet()
{
    cards.clear();
    cards.contains(Card());
}

// Randomly reorder all the cards in the set
void CardSet::shuffle()
{
    std::random_shuffle(cards.begin(), cards.end());
}

// Initialize card set attributes from JSON object
void CardSet::read(const QJsonObject &json)
{
    QJsonArray jsonCards = json["cards"].toArray();
    cards.clear();
    cards.reserve(jsonCards.size());
    for (qint8 index = 0; index < jsonCards.size(); ++index) {
        QJsonObject jsonCard = jsonCards[index].toObject();
        Card card;
        card.read(jsonCard);
        cards.append(card);
    }
}

// Add CardSet instance attributes to the JSON object argument
void CardSet::write(QJsonObject &json) const
{
    QJsonArray jsonCards;
    for (const Card &card : cards) {
        QJsonObject jsonCard;
        card.write(jsonCard);
        jsonCards.append(jsonCard);
    }
    json["cards"] = jsonCards;
}

// Overloaded == relational operator
// CardSet instances are equal if they contain equal cards in the same order
bool CardSet::operator ==(const CardSet& cardSet) const
{
    return this->cards == cardSet.cards;
}
