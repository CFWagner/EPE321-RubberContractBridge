#include "testplayergamestate.h"
#include "game-server/playergamestate.h"

// Default constructor
TestPlayerGameState::TestPlayerGameState(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of PlayerGameState class instance
void TestPlayerGameState::testPlayerGameState()
{
    // Initialise attributes
    GamePhase phase = BIDDING;
    Bid* currentBid = nullptr;
    Bid* contractBid = nullptr;
    qint8 gameNumber = 1;
    qint8 dealNumber = 0;
    qint8 trickNumber = 0;
    QVector<CardSet> tricks;
    PlayerPosition playerTurn = NORTH;
    PlayerPosition handToPlay = NORTH;
    PlayerPosition dealer = NORTH;
    PlayerPosition declarer = NORTH;
    bool teamVulnerable[2] = {false, false};
    Score score;
    GameEvent gameEvent = PLAY_START;
    QMap<PlayerPosition, QString> playerPositions;
    CardSet playerHand;
    CardSet dummyHand;

    // Construct PlayerGameState instance
    PlayerGameState playerState(phase, currentBid, contractBid, gameNumber, dealNumber,
                                trickNumber, tricks, playerTurn, handToPlay, dealer, declarer,
                                teamVulnerable, score, gameEvent, playerPositions, playerHand,
                                dummyHand);

    // Test PlayerGameState instance attributes
    QCOMPARE(playerState.getPhase(), phase);
    QCOMPARE(playerState.getCurrentBid(), nullptr);
    QCOMPARE(playerState.getContractBid(), nullptr);
    QCOMPARE(playerState.getGameNumber(), gameNumber);
    QCOMPARE(playerState.getDealNumber(), dealNumber);
    QCOMPARE(playerState.getTrickNumber(), trickNumber);
    QCOMPARE(playerState.getPlayerTurn(), playerTurn);
    QCOMPARE(playerState.getHandToPlay(), handToPlay);
    QCOMPARE(playerState.getDealer(), dealer);
    QCOMPARE(playerState.getDeclarer(), declarer);
    QCOMPARE(playerState.getTeamVulnerable(N_S), teamVulnerable[N_S]);
    QCOMPARE(playerState.getTeamVulnerable(E_W), teamVulnerable[E_W]);
    QCOMPARE(playerState.getEvent(), gameEvent);

    QJsonObject jsonPlayerState;
    playerState.write(jsonPlayerState);

    PlayerGameState playerState2;
    playerState2.read(jsonPlayerState);

    QCOMPARE(playerState2.getPhase(), phase);
    QCOMPARE(playerState2.getCurrentBid(), nullptr);
    QCOMPARE(playerState2.getContractBid(), nullptr);
    QCOMPARE(playerState2.getGameNumber(), gameNumber);
    QCOMPARE(playerState2.getDealNumber(), dealNumber);
    QCOMPARE(playerState2.getTrickNumber(), trickNumber);
    QCOMPARE(playerState2.getPlayerTurn(), playerTurn);
    QCOMPARE(playerState2.getHandToPlay(), handToPlay);
    QCOMPARE(playerState2.getDealer(), dealer);
    QCOMPARE(playerState2.getDeclarer(), declarer);
    QCOMPARE(playerState2.getTeamVulnerable(N_S), teamVulnerable[N_S]);
    QCOMPARE(playerState2.getTeamVulnerable(E_W), teamVulnerable[E_W]);
    QCOMPARE(playerState2.getEvent(), gameEvent);


    // Populate list attributes
//    CardSet trick1;
//    trick1.addCard(Card(SPADES, ACE));
//    trick1.addCard(Card(HEARTS, ACE));
//    trick1.addCard(Card(CLUBS, ACE));
//    trick1.addCard(Card(DIAMONDS, TWO));

//    CardSet trick2;
//    trick2.addCard(Card(SPADES, TWO));
//    trick2.addCard(Card(HEARTS, TWO));
//    trick2.addCard(Card(CLUBS, TWO));
//    trick2.addCard(Card(DIAMONDS, ACE));

//    tricks.append(trick1);
//    tricks.append(trick2);
}
