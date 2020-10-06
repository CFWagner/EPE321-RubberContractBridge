#include "testai.h"
#include <QtTest/QtTest>

testai::testai(QObject *parent) : QObject(parent)
{
}

//first tests are for for the following scenario
//contract bid of 1Spades with dummy hand spades Ace and player hand spades Ace
//2,K and Q of spades have been played
//Winning move will be the ACE
//Winning bid will be spades 2
void testai::setInitial()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    testAiHand.addCard(Card(SPADES,ACE));
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    //CardSuit suit, CardRank rank
    testSet.addCard(Card(SPADES,TWO));
    testSet.addCard(Card(SPADES,KING));
    testSet.addCard(Card(SPADES,QUEEN));
    QVector<CardSet> testTricks;
    testTricks.append(testSet);

    testcontractBid = new Bid(NORTH,SPADES,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);
}


void testai::testHandGenerate()
{
    setInitial();
    playerAI.updateGameState(player1);
    CardSet received;
    playerAI.initialMainSet();
    received = playerAI.getHand();
    qDebug() << "Testing hand length";
    QCOMPARE(received.getCardCount(),1);
    qDebug() << "Testing hand suit";
    QCOMPARE(received.getCard(0).getSuit(),SPADES);

}

void testai::testMoveGenerate()
{
    Card testmove;
    testmove = playerAI.guessMove();
    qDebug() <<"Did AI play correct card?";
    QCOMPARE(testmove.getRank(),ACE);
    QCOMPARE(testmove.getSuit(),SPADES);
}

void testai::testBidRX()
{
    Bid testBid;
    testBid = playerAI.getBidContract();
    qDebug() <<"Testing if bid received correct";
    QCOMPARE(testBid.getTricksAbove(),1);
    QCOMPARE(testBid.getTrumpSuit(),SPADES);
}


void testai::testBidGenerate()
{
    Bid testbid;
    playerAI.initialBidSet();
    testbid = playerAI.guessBid();
    qDebug() <<"Testing if bid correct";
    QCOMPARE(testbid.getTricksAbove(),2);
    QCOMPARE(testbid.getTrumpSuit(),SPADES);

}

//next test will follow the same but bid is Hearts thus check winning bid
//winning bid must be spades 2
void testai::setInitial2()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    testAiHand.addCard(Card(SPADES,ACE));
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    //CardSuit suit, CardRank rank
    testSet.addCard(Card(SPADES,TWO));
    testSet.addCard(Card(SPADES,KING));
    testSet.addCard(Card(SPADES,QUEEN));
    QVector<CardSet> testTricks;
    testTricks.append(testSet);

    testcontractBid = new Bid(NORTH,HEARTS,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);
}

void testai::testBidGenerate2()
{
    setInitial2();
    playerAI.updateGameState(player1);
    playerAI.initialBidSet();
    Bid testbid2 = playerAI.guessBid();
    qDebug() <<"Testing if bid 2 is correct";
    QCOMPARE(testbid2.getTricksAbove(),2);
    QCOMPARE(testbid2.getTrumpSuit(),SPADES);

}
//trickier hand. say I am first and second round
//I can't win ever but I know dummy has ACE but I have Q 10
//played were 8 9 K
//best would be to play 10 and save Q and let dummy do whatever;
//all is spades
void testai::setInitial3()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    testAiHand.addCard(Card(SPADES,QUEEN));
    testAiHand.addCard(Card(SPADES,TEN));
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    //CardSuit suit, CardRank rank
    testSet.addCard(Card(SPADES,EIGHT));
    testSet.addCard(Card(SPADES,NINE));
    testSet.addCard(Card(SPADES,KING));
    QVector<CardSet> testTricks;
    testTricks.append(testSet);

    testcontractBid = new Bid(NORTH,SPADES,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);

}
void testai::testMoveGanerate2()
{
    setInitial3();
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    Card testmove;
    testmove = playerAI.guessMove();
    qDebug() <<"Did AI play correct card?";
    //test if order works
    QCOMPARE(playerAI.canPlay.getCard(1).getRank(),QUEEN);
    qDebug()<<"Test second move";
    QCOMPARE(testmove.getRank(),TEN);
    QCOMPARE(testmove.getSuit(),SPADES);
}

//after this basics seem to work try edge cases
//what happens no dummy knowledge and first turn?
//setup H (2,3,4)
//S(j,k,q)
//trump suit it hearts
//so 2 Hearts???
//from pool should be 3 cards

void testai::setInitial4()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    testAiHand.addCard(Card(HEARTS,TWO));
    testAiHand.addCard(Card(HEARTS,THREE));
    testAiHand.addCard(Card(HEARTS,FOUR));
    testAiHand.addCard(Card(SPADES,JACK));
    testAiHand.addCard(Card(SPADES,TWO));
    //CardSuit suit, CardRank rank
    QVector<CardSet> testTricks;
    testTricks.append(testSet);
    testcontractBid = new Bid(NORTH,HEARTS,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);

}

void testai::testMoveGanerate3()
{
    setInitial4();
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    Card testmove;
    testmove = playerAI.guessMove();
    qDebug() <<"Did AI play correct card?";
    //test if order works
    QCOMPARE(playerAI.canPlay.getCard(0).getRank(),TWO);
    QCOMPARE(playerAI.canPlay.getCardCount(),3);
    qDebug()<<"Test second move";
    QCOMPARE(testmove.getRank(),TWO);
    QCOMPARE(testmove.getSuit(),HEARTS);

}
