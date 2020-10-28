#include "testbiddingphase.h"

testBiddingPhase::testBiddingPhase(QObject *parent) : QObject(parent)
{

}

testBiddingPhase::~testBiddingPhase()
{

}

void testBiddingPhase::testBid()
{
    // Greate four instances of the Bid phase to mimic four players.
    testBidN = new BidWindow();
    testBidE = new BidWindow();
    testBidS = new BidWindow();
    testBidW = new BidWindow();

    // Give all the players different names.
    testBidN->setName("Player 1");
    testBidE->setName("Player 2");
    testBidS->setName("Player 3");
    testBidW->setName("Player 4");

    //Wiat for North player to be visable.
    testBidN->showFullScreen();
    while (!testBidN->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);

    // Setup the signal that sends the various gamestates
    qRegisterMetaType<PlayerGameState>("PlayerGameState");
    qRegisterMetaType<Bid>("Bid");
    receiveBidN = new QSignalSpy(testBidN,SIGNAL(txBidSelected(Bid)));
    receiveBidS = new QSignalSpy(testBidS,SIGNAL(txBidSelected(Bid)));
    receiveBidE = new QSignalSpy(testBidE,SIGNAL(txBidSelected(Bid)));
    receiveBidW = new QSignalSpy(testBidW,SIGNAL(txBidSelected(Bid)));
    sendGS = new QSignalSpy(this,SIGNAL(updateGameState(PlayerGameState)));
    connect(this,&testBiddingPhase::updateGameState,testBidN,&BidWindow::getUpdateGameState);
    connect(this,&testBiddingPhase::updateGameState,testBidS,&BidWindow::getUpdateGameState);
    connect(this,&testBiddingPhase::updateGameState,testBidE,&BidWindow::getUpdateGameState);
    connect(this,&testBiddingPhase::updateGameState,testBidW,&BidWindow::getUpdateGameState);

    //Connect bid received slot
    QVERIFY(sendGS->isValid());
    QVERIFY(receiveBidN->isValid());
    QVERIFY(receiveBidS->isValid());


    // Setup gamestate for the bidding phase.
    // Initialise attributes
    //The bidding phase has started.
    GamePhase phase = BIDDING;
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
    GameEvent gameEvent = BID_START;
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
                            playerHand, dummyHand);

    //Send game state to all players
    emit updateGameState(playerBidPlay);
    QVERIFY(playerBidPlay.getEvent() == BID_START);


    //NORTH players start to Bid.
    QTest::mouseMove (testBidN, QPoint(630,310),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidN->childAt(630,310), Qt::LeftButton, Qt::NoModifier, QPoint(630,310),100);
    QTest::qWait(500);
    QList<QVariant> bidRec = receiveBidN->takeFirst();
    bidR = new Bid(qvariant_cast<Bid>(bidRec.at(0)).getBidder(),qvariant_cast<Bid>(bidRec.at(0)).getTrumpSuit(),qvariant_cast<Bid>(bidRec.at(0)).getTricksAbove());
    QVERIFY(qvariant_cast<Bid>(bidRec.at(0)).getBidder() == NORTH);

    //Send new gameState
    phase = BIDDING;
    currentBid = bidR;
    contractBid = bidR;
    gameNumber = 1; //First game
    dealNumber = 0; //No deals
    trickNumber = 0;
    playerTurn = EAST;
    handToPlay = EAST;
    dealer = NORTH;
    declarer = NORTH;
    gameEvent = PLAYER_BID;
    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");
    // Here the NORTH play is displayed.
    PlayerGameState playerBidPlay2(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            playerHand, dummyHand);
    emit updateGameState(playerBidPlay2);
    QVERIFY(playerBidPlay2.getEvent() == PLAYER_BID);
    //EAST players start to Bid.
    QTest::qWait(1000);
    testBidN->hide();
    QTest::qWait(500);
    testBidE->showFullScreen();
    QTest::qWait(500);
    QTest::mouseMove (testBidE, QPoint(630,410),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidE->childAt(630,410), Qt::LeftButton, Qt::NoModifier, QPoint(630,410),100);
    QTest::qWait(500);

    //EAST made bid.
    QList<QVariant> bidRec2 = receiveBidE->takeFirst();
    bidR = new Bid(qvariant_cast<Bid>(bidRec2.at(0)).getBidder(),qvariant_cast<Bid>(bidRec2.at(0)).getTrumpSuit(),qvariant_cast<Bid>(bidRec2.at(0)).getTricksAbove());
    QVERIFY(qvariant_cast<Bid>(bidRec2.at(0)).getTricksAbove() == 4);
    //Send new gameState
    phase = BIDDING;
    currentBid = bidR;
    contractBid = bidR;
    gameNumber = 1; //First game
    dealNumber = 0; //No deals
    trickNumber = 0;
    playerTurn = SOUTH;
    handToPlay = SOUTH;
    dealer = NORTH;
    declarer = NORTH;
    gameEvent = PLAYER_BID;
    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");

    PlayerGameState playerBidPlay3(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            playerHand, dummyHand);
    emit updateGameState(playerBidPlay3);
    QVERIFY(playerBidPlay3.getEvent() == PLAYER_BID);
    QTest::qWait(1000);
    testBidE->hide();
    QTest::qWait(500);
    testBidS->showFullScreen();
    QTest::qWait(500);
    QTest::mouseMove (testBidS, QPoint(830,510),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidS->childAt(830,510), Qt::LeftButton, Qt::NoModifier, QPoint(830,510),100);
    QTest::qWait(500);

    //SOUTH Made a bid
    QList<QVariant> bidRec3 = receiveBidS->takeFirst();
    bidR = new Bid(qvariant_cast<Bid>(bidRec3.at(0)).getBidder(),qvariant_cast<Bid>(bidRec3.at(0)).getTrumpSuit(),qvariant_cast<Bid>(bidRec3.at(0)).getTricksAbove());
    QVERIFY(qvariant_cast<Bid>(bidRec3.at(0)).getTricksAbove() == 7);
    //Send new gameState
    phase = BIDDING;
    currentBid = bidR;
    contractBid = bidR;
    gameNumber = 1; //First game
    dealNumber = 0; //No deals
    trickNumber = 0;
    playerTurn = WEST;
    handToPlay = WEST;
    dealer = NORTH;
    declarer = NORTH;
    gameEvent = PLAYER_BID;
    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");

    PlayerGameState playerBidPlay4(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            playerHand, dummyHand);
    emit updateGameState(playerBidPlay4);
    QVERIFY(playerBidPlay4.getEvent() == PLAYER_BID);
    QTest::qWait(1000);
    testBidS->hide();
    QTest::qWait(500);
    testBidW->showFullScreen();
    QTest::qWait(500);
    QTest::mouseMove (testBidW, QPoint(1300,410),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidW->childAt(1300,410), Qt::LeftButton, Qt::NoModifier, QPoint(1300,410),100);
    QTest::qWait(500);
    testBidW->hide();
    QTest::qWait(500);
    testBidN->showFullScreen();
    QTest::qWait(500);
    QTest::mouseMove (testBidN, QPoint(1300,410),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidN->childAt(1300,410), Qt::LeftButton, Qt::NoModifier, QPoint(1300,410),100);
    QTest::qWait(500);
    testBidN->hide();
    QTest::qWait(500);
    testBidE->showFullScreen();
    QTest::qWait(500);
    QTest::mouseMove (testBidE, QPoint(1300,410),-1);
    QTest::qWait(500);
    QTest::mouseClick (testBidE->childAt(1300,410), Qt::LeftButton, Qt::NoModifier, QPoint(1300,410),100);
    QTest::qWait(1000);
    testBidN->close();
    testBidS->close();
    testBidW->close();
    testBidE->close();
}
