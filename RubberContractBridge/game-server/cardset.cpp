#include "cardset.h"
#include <algorithm>
#include <QJsonArray>

// Default constructor
CardSet::CardSet()
{
    cards = QVector<Card>();
}

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

// Return and remove card at given position from set. The top of the set is located at index 0
Card CardSet::getCard(qint8 position)
{
    return cards.value(position);
}

// Getter for number of cards currently in the card set
qint8 CardSet::getCardCount()
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
