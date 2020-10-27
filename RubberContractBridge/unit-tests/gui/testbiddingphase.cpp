#include "testbiddingphase.h"

testBiddingPhase::testBiddingPhase(QObject *parent) : QObject(parent)
{

}

testBiddingPhase::~testBiddingPhase()
{

}

void testBiddingPhase::testBid()
{
    testBidN = new BidWindow();
    testBidN->showFullScreen();
    while (!testBidN->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);
    qRegisterMetaType<PlayerGameState>("PlayerGameState");
    connect(this,&testBiddingPhase::updateGameState,testBidN,&BidWindow::getUpdateGameState);

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
    PlayerGameState playerN(phase, currentBid, contractBid, gameNumber, dealNumber,
                            trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                            dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                            playerHand, dummyHand);
    //emit updateGameState(playerN);

}
