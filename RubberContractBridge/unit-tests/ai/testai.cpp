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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
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
    qint8 testTricksWon[4];

    testcontractBid = new Bid(NORTH,SPADES,1);
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1,testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);
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
    qDebug() <<"Testing if first element in deck is a TWO of CLUBS";
    QCOMPARE(testDeck.getCard(0).getSuit(),CLUBS);
    QCOMPARE(testDeck.getCard(0).getRank(),TWO);
    qDebug() <<"Testing if last element in deck is an ACE of SPADES";
    QCOMPARE(testDeck.getCard(testDeck.getCardCount()-1).getSuit(),SPADES);
    QCOMPARE(testDeck.getCard(testDeck.getCardCount()-1).getRank(),ACE);
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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);
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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,3,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);

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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);

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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);
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
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);
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

//Tests concerning the random number generator will be done here, since Test ai always uses system time to seed
// The results should very. These tests will see how much does seeding it effect the distribution
//First it will be seeded once then it will be seeded every call withm time(0).
//The hope is both should be roughly the same and should much normal distribution.
uint32_t testai::random()
{
    seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;

}
float testai::rangeGen(float min, float max)
{
    return ((float)random() / (float)(0x7FFFFFFF)) * (max/2 - min) + min;
}

float testai::calculateMean(float data[], int length)
{
    float sum = 0.0, mean = 0.0;
    for(int i = 0; i < length; ++i)
    {
        sum += data[i];
    }
    mean = sum/length;
    return mean;

}
//First test will check the std of the data set
float testai::calculateSTD(float data[], int length)
{
    float mean, standardDeviation = 0.0;
    mean = calculateMean(data,length);
    for(int i = 0; i < length; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / length);


}

//Generate a set of values simulating normal distribution of values between 100 and 0

float testai::generatesNormalDistribution()
{
    QVector<float> dataPoints;
    int size = 100;
    int repititions = 10;
    float lower=0.0;
    float upper= 100.0;
    float dataSet[size*repititions+repititions];

    for (int i=0;i<repititions;i++)
    {
        for (float j=lower;j<upper+1.0;j++)
        {
            dataPoints.append(j);
        }
    }
    for (int i=0;i<size*repititions+repititions;i++)
    {
        dataSet[i]=dataPoints.value(i);
    }
    UniformMean = calculateMean(dataSet,size*repititions+repititions);
    float answerSTD = calculateSTD(dataSet,size*repititions+repititions);
    return answerSTD;

}
//This test will be seeding the generator once and seeing how it performs
float testai::testGeneratorNoSeed()
{
    //generating 10 000 numbers between 0 and 100
    int size = 10000;
    float lower=0.0;
    float upper= 100.0;
    float dataSet[size];
    seed = 0;
    for (int i=0;i<size;i++)
    {
        dataSet[i]=rangeGen(lower,upper);
    }
    NoSeedMean = calculateMean(dataSet,size);
    float answerSTD = calculateSTD(dataSet,size);
    return answerSTD;
}

//seeding the values after every call
float testai::testGeneratorSeeded()
{
    //generating 10 000 numbers between 0 and 100
    int size = 10000;
    float lower=0.0;
    float upper= 100.0;
    float dataSet[size];
    for (int i=0;i<size;i++)
    {
        seed = i;
        dataSet[i]=rangeGen(lower,upper);
    }
    SeedMean = calculateMean(dataSet,size);
    float answerSTD = calculateSTD(dataSet,size);
    return answerSTD;

}

//Get's values from functions in line 377 and 396
//Compares if they are in a simaler range if it is set's a flag to true
//Creates a normal distribution function (the value 0-100 each ten times)
//Sees if lemer is a normal distribution
void testai::testingGenerator()
{
    float STDoneSeed = testGeneratorNoSeed();
    float STDSeed = testGeneratorSeeded();
    float STDNormal = generatesNormalDistribution();
    //First test if the normal distribution average is correct and std is correct within error
    //set error tolerance to 10%
    float expectedNormMedian = 50.0;
    bool isInExpectNormMedian = false;
    if ((expectedNormMedian*0.9<=UniformMean) && (expectedNormMedian*1.10>=UniformMean))
    {
        isInExpectNormMedian=true;
    }
    qDebug()<<"Verify mean of normal distribution";
    QVERIFY(isInExpectNormMedian);
    qDebug()<<"Verify std of normal distribution";
    bool isInExpectNormSTD = false;
    //This value was generated by python multiply by 100 to get std for [0,100] normal distribution
    float STDBetweenOneZero =  0.2887;
    float expectedNormSTD = STDBetweenOneZero*100;
    if ((expectedNormSTD*0.9<=STDNormal) && (expectedNormSTD*1.10>=STDNormal))
    {
        isInExpectNormSTD=true;
    }
    QVERIFY(isInExpectNormSTD);
    //Now check if both the seeded and non seeded lehmer values match Normal distribution
    qDebug()<<"Verify mean of non-Seeded Lehmer";
    isInExpectNormMedian = false;
    if ((expectedNormMedian*0.9<=NoSeedMean) && (expectedNormMedian*1.10>=NoSeedMean))
        {
            isInExpectNormMedian=true;
        }
    QVERIFY(isInExpectNormMedian);
    isInExpectNormSTD = false;
    if ((expectedNormSTD*0.9<=STDoneSeed) && (expectedNormSTD*1.10>=STDoneSeed))
        {
            isInExpectNormSTD=true;
        }
    qDebug()<<"Verify std of non-Seeded Lehmer";
        QVERIFY(isInExpectNormSTD);
        qDebug()<<"Verify mean of Seeded Lehmer";
        isInExpectNormMedian = false;
        if ((expectedNormMedian*0.9<=SeedMean) && (expectedNormMedian*1.10>=SeedMean))
            {
                isInExpectNormMedian=true;
            }
        QVERIFY(isInExpectNormMedian);
        isInExpectNormSTD = false;
        if ((expectedNormSTD*0.9<=STDSeed) && (expectedNormSTD*1.10>=STDSeed))
            {
                isInExpectNormSTD=true;
            }
        qDebug()<<"Verify std of Seeded Lehmer";
            QVERIFY(isInExpectNormSTD);
      //To check if the lehmer is susceptable to seeding verify between once seeding and continious seeding
      //If values are within error there is no real difference thus lehmer is safe to use time(0) as seed
      qDebug()<<"Verify no difference between mean in seed and non-seed";
      isInExpectNormMedian = false;
      if ((NoSeedMean*0.9<=SeedMean) && (NoSeedMean*1.10>=SeedMean))
          {
              isInExpectNormMedian=true;
          }
      QVERIFY(isInExpectNormMedian);
      qDebug()<<"Verify no difference between std in seed and non-seed";
      isInExpectNormSTD = false;
      if ((STDoneSeed*0.9<=STDSeed) && (STDoneSeed*1.10>=STDSeed))
          {
              isInExpectNormSTD=true;
          };
          QVERIFY(isInExpectNormSTD);

//Last test checks if all values are indeed between [0,100]
//Thus setup new test data and loop through it until exception set flag to false
      bool isValid = true;
      int total = 0;
      //generating 10 000 numbers between 0 and 100
      int size = 10000;
      float lower=0.0;
      float upper= 100.0;
      float dataSet[size];
      //just to make sure a seed that hasn't been used yet is used
      seed = 10001;
      for (int i=0;i<size;i++)
      {
          dataSet[i]=rangeGen(lower,upper);
          if ((dataSet[i]<0) || (dataSet[i]>100))
          {
              isValid = false;
          }
          if (dataSet[i]<20)
          {
              total++;
          }
      }
      qDebug()<<"Are values in interval [0,100]";
      QVERIFY(isValid);
      float percentage = (static_cast<float>(total)/static_cast<float>(size)) *100.0;
      //The aim is for events to have say 20% chance every number has equal chance so assumption is
      // if (x<20) should happen roughly 20% of the time. Test this within confidence of 90%
      qDebug()<<"Is assumption in line 544 correct";
      isValid = false;
      if ((20*0.9<=percentage) && (20*1.10>=percentage))
          {
          isValid = true;
      }
      QVERIFY(isValid);


}


//This will test the recovery feature for a bid and trick
//Check if new card is played if it's flagged that the move was incorrect
void testai::testingRecovery()
{
    //use initial set 6 for state
    setInitial6();
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    Card firstMove = playerAI.guessMove();
    Bid firstBid = playerAI.guessBid();
    playerAI.notifyBidRejected("Some reason");
    playerAI.notifyMoveRejected("Some reason");
    Card secondMove = playerAI.cardRecovered;
    Bid secondBid = playerAI.bidRecovered;
    qDebug()<<"Check if the moves are different";
    bool isValid=true;
    if (firstMove==secondMove)
    {
        isValid=false;
    }
    QVERIFY(isValid);
    qDebug()<<"Check if the bids are different";
    isValid=true;
    if (firstBid==secondBid)
    {
        isValid=false;
    }
    QVERIFY(isValid);


}


//Testing bidlist generation
void testai::setInitial7()
{
    QMap<PlayerPosition,QString> testMap;
    QMap<PlayerPosition,qint8> testCardCountMap;
    Score testScore=Score();
    qint8 testTricksWon[4];
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
    player1 = PlayerGameState(CARDPLAY,testcontractBid,testcontractBid,1,1,1, testTricks,testTricksWon,EAST,EAST,EAST,NORTH,
                                              testScore,PLAY_START,testMap,testCardCountMap,testAiHand,testDummyHand);
}
//Last bid was 1NT so there should only be 30 valid options and nothing below it
void testai::testingBidListGenerate()
{
    setInitial7();
    Bid bidNow = Bid(NORTH,NONE,1);
    playerAI.updateGameState(player1);
    playerAI.initialMainSet();
    playerAI.generatebidlist();
    qDebug()<<"Testing the initial bid list size";
    QCOMPARE(playerAI.bidlist.length(),35);
    playerAI.removebids();
    qDebug()<<"Testing the bid list size";
    QCOMPARE(playerAI.bidlist.length(),30);
    qDebug()<<"Testing if no possible bid is lower than current";
    bool isValid = true;
    for (int i=0;i<playerAI.bidlist.length();i++)
    {
        if (bidNow>playerAI.bidlist.value(i))
        {
            qDebug()<<playerAI.bidlist.value(i).getTricksAbove();
            qDebug()<<playerAI.bidlist.value(i).getTrumpSuit();
            isValid=false;
        }
    }
    QVERIFY(isValid);

}

