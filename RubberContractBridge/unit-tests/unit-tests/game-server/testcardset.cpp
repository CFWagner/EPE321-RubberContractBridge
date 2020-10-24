#include "testcardset.h"

// Default constructor
TestCardSet::TestCardSet(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of CardSet class instance
void TestCardSet::testCardSet()
{ 
    CardSet cardSet1;

    // Add cards to card set
    Card card1 = Card(SPADES, JACK);
    Card card2 = Card(CLUBS, TWO);
    Card card3 = Card(HEARTS, SEVEN);
    Card card4 = Card(DIAMONDS, ACE);
    cardSet1.addCard(card1);
    cardSet1.addCard(card2);
    cardSet1.addCard(card3);
    cardSet1.addCard(card4);

    // Test for correct card set state
    QCOMPARE(cardSet1.getCard(0) == card1, true);
    QCOMPARE(cardSet1.getCard(1) == card2, true);
    QCOMPARE(cardSet1.getCard(2) == card3, true);
    QCOMPARE(cardSet1.getCard(3) == card4, true);
    QCOMPARE(cardSet1.getCardCount() == 4, true);

    // Remove card
    Card removedCard1 = cardSet1.removeCard(1);

    // Test for correct card set state
    QCOMPARE(removedCard1 == card2, true);
    QCOMPARE(cardSet1.getCard(0) == card1, true);
    QCOMPARE(cardSet1.getCard(1) == card3, true);
    QCOMPARE(cardSet1.getCard(2) == card4, true);
    QCOMPARE(cardSet1.getCardCount() == 3, true);

    // Remove all cards
    cardSet1.clearSet();
    QCOMPARE(cardSet1.getCardCount() == 0, true);

    // Populate card set with all of the 52 different cards
    for(qint8 suitVal = CLUBS; suitVal <= SPADES; suitVal++){
        CardSuit suit = CardSuit(suitVal);
        for(qint8 rankVal = TWO; rankVal <= ACE; rankVal++){
            CardRank rank = CardRank(rankVal);
            Card card(suit, rank);
            cardSet1.addCard(card);
        }
    }

    // Test all cards are in order according to CardSuit then CardRank enums
    cardSet1.orderHand();
    for(qint8 pos = 0; pos < cardSet1.getCardCount() - 1; pos++){
        Card firstCard = cardSet1.getCard(pos);
        Card secondCard = cardSet1.getCard(pos + 1);
        if(firstCard.getSuit() == secondCard.getSuit())
            QCOMPARE(firstCard.getRank() < secondCard.getRank(), true);
        else
            QCOMPARE(firstCard.getSuit() < secondCard.getSuit(), true);
    }

    // Generate QJsonObject instance from CardSet object
    QJsonObject jsonCardSet;
    cardSet1.write(jsonCardSet);

    // Test that QJsonObject instance contains correct keys
    QCOMPARE(jsonCardSet.contains("cards"), true);

    // Initialize CardSet object using QJsonObject instance
    CardSet cardSet2;
    cardSet2.read(jsonCardSet);

    // Test for correct CardSet state
    QCOMPARE(cardSet1, cardSet2);
}
