#include "testai.h"
#include <QtTest/QtTest>
//No continious game need to be simulated since everything stems from a gamestate so I will receive a knew one every time
//TLDR found edge case when dummy is null and trick amount is null
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

//This will be used to check if the AI correctly generates a 52 card deck in ascending order
void testai::testDeckGeneration()
{
    playerAI.generatedeck();
    CardSet testDeck;
    testDeck = playerAI.getDeck();
    qDebug() <<"Testing if first element in deck is an ACE of CLUBS";
    QCOMPARE(testDeck.getCard(0).getSuit(),CLUBS);
    QCOMPARE(testDeck.getCard(0).getRank(),ACE);
    qDebug() <<"Testing if last element in deck is a KING of SPADES";
    QCOMPARE(testDeck.getCard(testDeck.getCardCount()-1).getSuit(),SPADES);
    QCOMPARE(testDeck.getCard(testDeck.getCardCount()-1).getRank(),KING);
    qDebug() << "Testing if the deck is of size 52";
    QCOMPARE(testDeck.getCardCount(),52);

}

//Testing to see if removal tool correctly removes all impossible cards from possibilities.
void testai::testDeckRemoval()
{
   setInitial();
   playerAI.updateGameState(player1);
    playerAI.generatedeck();
   playerAI.removecards(playerAI.myhand);
   CardSet testDeck;
   testDeck = playerAI.getDeck();
   qDebug() <<"Testing if the same amount of cards as in my hand was removed";
   QCOMPARE(testDeck.getCardCount(),52-playerAI.myhand.getCardCount());


;}
//next test will follow the same but bid is Hearts thus check winning bid
//winning bid must be spades 2 since i have high card ACE
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
//trump suit is hearts
//so 2 Hearts since no knowledge???
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
    //test if selection generator has worked
    QCOMPARE(playerAI.canPlay.getCard(0).getRank(),TWO);
    QCOMPARE(playerAI.canPlay.getCardCount(),3);
    qDebug()<<"Test third move";
    QCOMPARE(testmove.getRank(),TWO);
    QCOMPARE(testmove.getSuit(),HEARTS);

}
//What happens if NT and low cards from different suits but I have a winning card highest suit
//I am last in the round as defender
//The tricks will be D2,H2,S5
//my hand will be H3,H4,D3,S6
//S6 wins this trick so expected to play that
//Available card pool should be one since only S6 wins
void testai::setInitial5()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    testAiHand.addCard(Card(HEARTS,THREE));
    testAiHand.addCard(Card(HEARTS,FOUR));
    testAiHand.addCard(Card(SPADES,SIX));
    testAiHand.addCard(Card(DIAMONDS,SIX));
    //CardSuit suit, CardRank rank
    testSet.addCard(Card(DIAMONDS,TWO));
    testSet.addCard(Card(HEARTS,TWO));
    testSet.addCard(Card(SPADES,FIVE));
    QVector<CardSet> testTricks;
    testTricks.append(testSet);
    testcontractBid = new Bid(NORTH,NONE,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);
}
void testai::testMoveGanerate4()
{
    setInitial5();
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    Card testmove;
    testmove = playerAI.guessMove();
    qDebug() <<"Did AI play correct card?";
    //test if selection of available condidates works
    QCOMPARE(playerAI.canPlay.getCard(0).getRank(),SIX);
    QCOMPARE(playerAI.canPlay.getCardCount(),1);
    qDebug()<<"Test fourth move";
    QCOMPARE(testmove.getRank(),SIX);
    QCOMPARE(testmove.getSuit(),SPADES);

}

//Spades is now removed so no card will beat current trick thus play D6
void testai::setInitial6()
{
    QMap<PlayerPosition,QString> testMap;
    Score testScore=Score();
    bool testVulnerable[2];
    const Bid* testcontractBid;
    CardSet testSet;
    CardSet testAiHand;
    CardSet testDummyHand;
    testDummyHand.addCard(Card(SPADES,ACE));
    testAiHand.addCard(Card(HEARTS,THREE));
    testAiHand.addCard(Card(HEARTS,FOUR));
    testAiHand.addCard(Card(DIAMONDS,SIX));
    //CardSuit suit, CardRank rank
    testSet.addCard(Card(DIAMONDS,TWO));
    testSet.addCard(Card(HEARTS,TWO));
    testSet.addCard(Card(SPADES,FIVE));
    QVector<CardSet> testTricks;
    testTricks.append(testSet);
    testcontractBid = new Bid(NORTH,NONE,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,EAST,EAST,EAST,NORTH,testVulnerable,
                                              testScore,PLAY_START,testMap,testAiHand,testDummyHand);
}

void testai::testMoveGanerate5()
{
    setInitial6();
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    Card testmove;
    testmove = playerAI.guessMove();
    qDebug() <<"Did AI play correct card?";
    //test if selection of available condidates works
    QCOMPARE(playerAI.canPlay.getCard(0).getRank(),SIX);
    QCOMPARE(playerAI.canPlay.getCardCount(),3);
    qDebug()<<"Test fith move";
    QCOMPARE(testmove.getRank(),SIX);
    QCOMPARE(testmove.getSuit(),DIAMONDS);

}
