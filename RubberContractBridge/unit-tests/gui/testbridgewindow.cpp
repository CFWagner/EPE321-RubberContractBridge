#include "testbridgewindow.h"

testBridgeWindow::testBridgeWindow(QObject *parent) : QObject(parent)
{

}

testBridgeWindow::~testBridgeWindow()
{

}

void testBridgeWindow::testBridge()
{
      testPlayN = new bridgeWindow();
      testPlayE = new bridgeWindow();
      testPlayS = new bridgeWindow();
      testPlayW = new bridgeWindow();
      testPlayN->showFullScreen();
    while (!testPlayN->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);

    sendGS = new QSignalSpy(this,SIGNAL(updateGameState(PlayerGameState)));
    connect(this,&testBridgeWindow::updateGameState,testPlayN,&bridgeWindow::getUpdateGameState);
    connect(this,&testBridgeWindow::updateGameState,testPlayE,&bridgeWindow::getUpdateGameState);
    connect(this,&testBridgeWindow::updateGameState,testPlayS,&bridgeWindow::getUpdateGameState);
    connect(this,&testBridgeWindow::updateGameState,testPlayW,&bridgeWindow::getUpdateGameState);
    // Manually assign player hands
    CardSet northHand;
    CardSet eastHand;
    CardSet southHand;
    CardSet westHand;

    northHand.addCard(Card(CLUBS, ACE));
    northHand.addCard(Card(CLUBS, TWO));
    northHand.addCard(Card(CLUBS, THREE));
    northHand.addCard(Card(DIAMONDS, FIVE));
    northHand.addCard(Card(HEARTS, NINE));
    northHand.addCard(Card(SPADES, SEVEN));
    northHand.addCard(Card(SPADES, KING));
    northHand.addCard(Card(HEARTS, FIVE));
    northHand.addCard(Card(CLUBS, SIX));
    northHand.addCard(Card(CLUBS, FIVE));
    northHand.addCard(Card(DIAMONDS, NINE));
    northHand.addCard(Card(DIAMONDS, QUEEN));
    northHand.addCard(Card(SPADES, NINE));

    eastHand.addCard(Card(DIAMONDS, ACE));
    eastHand.addCard(Card(HEARTS, TWO));
    eastHand.addCard(Card(DIAMONDS, THREE));
    eastHand.addCard(Card(CLUBS, QUEEN));
    eastHand.addCard(Card(CLUBS, TEN));
    eastHand.addCard(Card(CLUBS, NINE));
    eastHand.addCard(Card(CLUBS, FOUR));
    eastHand.addCard(Card(DIAMONDS, TEN));
    eastHand.addCard(Card(DIAMONDS, EIGHT));
    eastHand.addCard(Card(DIAMONDS, SEVEN));
    eastHand.addCard(Card(HEARTS, KING));
    eastHand.addCard(Card(HEARTS, JACK));
    eastHand.addCard(Card(HEARTS, SEVEN));

    southHand.addCard(Card(DIAMONDS, TWO));
    southHand.addCard(Card(HEARTS, ACE));
    southHand.addCard(Card(HEARTS, THREE));
    southHand.addCard(Card(DIAMONDS, FOUR));
    southHand.addCard(Card(DIAMONDS, KING));
    southHand.addCard(Card(DIAMONDS, JACK));
    southHand.addCard(Card(SPADES, JACK));
    southHand.addCard(Card(SPADES, FIVE));
    southHand.addCard(Card(DIAMONDS, SIX));
    southHand.addCard(Card(HEARTS, QUEEN));
    southHand.addCard(Card(HEARTS, EIGHT));
    southHand.addCard(Card(CLUBS, SEVEN));
    southHand.addCard(Card(SPADES, FOUR));

    westHand.addCard(Card(SPADES, ACE));
    westHand.addCard(Card(SPADES, TWO));
    westHand.addCard(Card(SPADES, THREE));
    westHand.addCard(Card(CLUBS, EIGHT));
    westHand.addCard(Card(HEARTS, FOUR));
    westHand.addCard(Card(SPADES, QUEEN));
    westHand.addCard(Card(SPADES, SIX));
    westHand.addCard(Card(CLUBS, KING));
    westHand.addCard(Card(HEARTS, TEN));
    westHand.addCard(Card(HEARTS, SIX));
    westHand.addCard(Card(SPADES, EIGHT));
    westHand.addCard(Card(CLUBS, JACK));
    westHand.addCard(Card(SPADES, TEN));

    QMap<PlayerPosition, CardSet> playerHands;
    playerHands.insert(NORTH, northHand);
    playerHands.insert(EAST, eastHand);
    playerHands.insert(SOUTH, southHand);
    playerHands.insert(WEST, westHand);

    GamePhase phase = CARDPLAY;
    Bid* currentBid = nullptr; //No bids yet
    Bid* contractBid = nullptr; //No bids
    qint8 gameNumber = 1; //First game
    qint8 dealNumber = 0; //No deals
    qint8 trickNumber = 0;
    QVector<CardSet> tricks;
    qint8 tricksWon[4] = {0, 0, 0, 0};
    PlayerPosition playerTurn = NORTH;
    PlayerPosition handToPlay = NORTH;
    PlayerPosition dealer = NORTH;
    PlayerPosition declarer = NORTH;
    Score score;
    GameEvent gameEvent = PLAY_START;
    QMap<PlayerPosition, QString> playerPositions;
    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");
    QMap<PlayerPosition, qint8> playerCardCount;
    CardSet playerHand;
    CardSet dummyHand;
    // Create the player game state from the above information
    PlayerGameState playerBidPlay(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            northHand, southHand);
    emit updateGameState(playerBidPlay);
    QTest::qWait(3000);
    testPlayN->hide();
    PlayerGameState playerBidPlay2(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            eastHand, southHand);
    emit updateGameState(playerBidPlay2);
    testPlayE->showFullScreen();
    QTest::qWait(3000);
    testPlayE->hide();
    PlayerGameState playerBidPlay3(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            southHand, southHand);
    emit updateGameState(playerBidPlay3);
    testPlayS->showFullScreen();
    QTest::qWait(3000);
    testPlayS->hide();
    PlayerGameState playerBidPlay4(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            westHand, southHand);
    emit updateGameState(playerBidPlay4);
    testPlayW->showFullScreen();
    QTest::qWait(6000);
    QVERIFY(sendGS->isValid());
    QCOMPARE(westHand,playerBidPlay4.getPlayerHand());
    QCOMPARE(eastHand,playerBidPlay2.getPlayerHand());
    QCOMPARE(southHand,playerBidPlay3.getPlayerHand());
    QCOMPARE(northHand,playerBidPlay.getPlayerHand());
    testPlayN->close();
    testPlayS->close();
    testPlayW->close();
    testPlayE->close();

}
