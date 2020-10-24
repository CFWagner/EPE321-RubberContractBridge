#include "testcard.h"
#include<QDebug>

// Default constructor
TestCard::TestCard(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of Card class instance
void TestCard::testCard()
{
    // Construct Card object with valid constructor arguments.
    // Invalid arguments not possible due to enums.
    CardSuit suit = CLUBS;
    CardRank rank = SEVEN;
    Card card1(suit, rank);

    // Test for correct Card object state
    QCOMPARE(rank, card1.getRank());
    QCOMPARE(suit, card1.getSuit());

    // Generate QJsonObject instance from Card object
    QJsonObject jsonCard;
    card1.write(jsonCard);

    // Test that QJsonObject instance contains correct keys
    QCOMPARE(jsonCard.contains("suit"), true);
    QCOMPARE(jsonCard.contains("rank"), true);

    // Test that correct values are present in QJsonObject instance
    QCOMPARE(jsonCard.value("suit") == suit, true);
    QCOMPARE(jsonCard.value("rank") == rank, true);

    // Initialize Card object using QJsonObject instance
    Card card2;
    card2.read(jsonCard);

    // Test for correct Card object state
    QCOMPARE(rank, card2.getRank());
    QCOMPARE(suit, card2.getSuit());
}
