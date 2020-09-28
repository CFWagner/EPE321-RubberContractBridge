#include "cardset.h"

CardSet::CardSet()
{
    cards = QVector<Card>();
}

void CardSet::addCard(Card card)
{
    cards.append(card);
}

Card CardSet::removeCard(qint8 position)
{
    return cards.takeAt(position);
}

Card CardSet::getCard(qint8 position)
{
    return cards.value(position);
}

qint8 CardSet::getCardCount()
{
    return cards.count();
}

void CardSet::orderHand(CardSuit trumpSuit)
{

}

void CardSet::clearSet()
{
    cards.clear();
}

void CardSet::shuffle()
{

}

void CardSet::read(const QJsonObject &json)
{

}

void CardSet::write(const QJsonObject &json)
{

}

QString CardSet::toString()
{
    return "";
}
