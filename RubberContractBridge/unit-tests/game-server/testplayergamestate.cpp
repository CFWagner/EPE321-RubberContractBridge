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

    // Compare list based attributes
    for(qint8 i = 0; i < tricks.size(); ++ i){
        for(qint8 j = 0; j < tricks[i].getCardCount(); ++ j){
            QCOMPARE(playerState.getTricks()[i].getCard(j) == tricks[i].getCard(j), true);
        }
    }
    for(qint8 j = 0; j < playerHand.getCardCount(); ++ j)
        QCOMPARE(playerState.getPlayerHand().getCard(j) == playerHand.getCard(j), true);

    for(qint8 j = 0; j < dummyHand.getCardCount(); ++ j)
        QCOMPARE(playerState.getDummyHand().getCard(j) == dummyHand.getCard(j), true);

    for(qint8 position = NORTH; position <= WEST; ++ position){
        QCOMPARE(playerState.getPlayerName(PlayerPosition(position)),
                 playerPositions.value(PlayerPosition(position)));
    }

    // Read to and write from JSON object with object attributes that are nullptr or empty lists
    QJsonObject jsonPlayerState;
    playerState.write(jsonPlayerState);
    PlayerGameState playerState2;
    playerState2.read(jsonPlayerState);

    // Test target PlayerGameState instance attributes
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

    // Compare list based attributes
    for(qint8 i = 0; i < tricks.size(); ++ i){
        for(qint8 j = 0; j < tricks[i].getCardCount(); ++ j){
            QCOMPARE(playerState2.getTricks()[i].getCard(j) == tricks[i].getCard(j), true);
        }
    }
    for(qint8 j = 0; j < playerHand.getCardCount(); ++ j)
        QCOMPARE(playerState2.getPlayerHand().getCard(j) == playerHand.getCard(j), true);

    for(qint8 j = 0; j < dummyHand.getCardCount(); ++ j)
        QCOMPARE(playerState2.getDummyHand().getCard(j) == dummyHand.getCard(j), true);

    for(qint8 position = NORTH; position <= WEST; ++ position){
        QCOMPARE(playerState2.getPlayerName(PlayerPosition(position)),
                 playerPositions.value(PlayerPosition(position)));
    }


    // Populate list attributes
    CardSet trick1;
    trick1.addCard(Card(SPADES, ACE));
    trick1.addCard(Card(HEARTS, ACE));
    trick1.addCard(Card(CLUBS, ACE));
    trick1.addCard(Card(DIAMONDS, TWO));

    CardSet trick2;
    trick2.addCard(Card(SPADES, TWO));
    trick2.addCard(Card(HEARTS, TWO));
    trick2.addCard(Card(CLUBS, TWO));
    trick2.addCard(Card(DIAMONDS, ACE));

    tricks.append(trick1);
    tricks.append(trick2);

    playerHand.addCard(Card(SPADES, THREE));
    playerHand.addCard(Card(HEARTS, THREE));
    playerHand.addCard(Card(CLUBS, THREE));
    playerHand.addCard(Card(DIAMONDS, THREE));

    dummyHand.addCard(Card(SPADES, FOUR));
    dummyHand.addCard(Card(HEARTS, FOUR));
    dummyHand.addCard(Card(CLUBS, FOUR));
    dummyHand.addCard(Card(DIAMONDS, FOUR));

    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");

    // Construct PlayerGameState instance
    PlayerGameState playerState3(phase, currentBid, contractBid, gameNumber, dealNumber,
                                trickNumber, tricks, playerTurn, handToPlay, dealer, declarer,
                                teamVulnerable, score, gameEvent, playerPositions, playerHand,
                                dummyHand);

    // Test PlayerGameState instance attributes
    QCOMPARE(playerState3.getPhase(), phase);
    QCOMPARE(playerState3.getCurrentBid(), nullptr);
    QCOMPARE(playerState3.getContractBid(), nullptr);
    QCOMPARE(playerState3.getGameNumber(), gameNumber);
    QCOMPARE(playerState3.getDealNumber(), dealNumber);
    QCOMPARE(playerState3.getTrickNumber(), trickNumber);
    QCOMPARE(playerState3.getPlayerTurn(), playerTurn);
    QCOMPARE(playerState3.getHandToPlay(), handToPlay);
    QCOMPARE(playerState3.getDealer(), dealer);
    QCOMPARE(playerState3.getDeclarer(), declarer);
    QCOMPARE(playerState3.getTeamVulnerable(N_S), teamVulnerable[N_S]);
    QCOMPARE(playerState3.getTeamVulnerable(E_W), teamVulnerable[E_W]);
    QCOMPARE(playerState3.getEvent(), gameEvent);

    // Compare list based attributes
    for(qint8 i = 0; i < tricks.size(); ++ i){
        for(qint8 j = 0; j < tricks[i].getCardCount(); ++ j){
            QCOMPARE(playerState3.getTricks()[i].getCard(j) == tricks[i].getCard(j), true);
        }
    }
    for(qint8 j = 0; j < playerHand.getCardCount(); ++ j)
        QCOMPARE(playerState3.getPlayerHand().getCard(j) == playerHand.getCard(j), true);

    for(qint8 j = 0; j < dummyHand.getCardCount(); ++ j)
        QCOMPARE(playerState3.getDummyHand().getCard(j) == dummyHand.getCard(j), true);

    for(qint8 position = NORTH; position <= WEST; ++ position){
        QCOMPARE(playerState3.getPlayerName(PlayerPosition(position)),
                 playerPositions.value(PlayerPosition(position)));
    }

    // Read to and write from JSON object with object attributes that are nullptr or empty lists
    QJsonObject jsonPlayerState3;
    playerState3.write(jsonPlayerState);
    PlayerGameState playerState4;
    playerState4.read(jsonPlayerState);

    // Test target PlayerGameState instance attributes
    QCOMPARE(playerState4.getPhase(), phase);
    QCOMPARE(playerState4.getCurrentBid(), nullptr);
    QCOMPARE(playerState4.getContractBid(), nullptr);
    QCOMPARE(playerState4.getGameNumber(), gameNumber);
    QCOMPARE(playerState4.getDealNumber(), dealNumber);
    QCOMPARE(playerState4.getTrickNumber(), trickNumber);
    QCOMPARE(playerState4.getPlayerTurn(), playerTurn);
    QCOMPARE(playerState4.getHandToPlay(), handToPlay);
    QCOMPARE(playerState4.getDealer(), dealer);
    QCOMPARE(playerState4.getDeclarer(), declarer);
    QCOMPARE(playerState4.getTeamVulnerable(N_S), teamVulnerable[N_S]);
    QCOMPARE(playerState4.getTeamVulnerable(E_W), teamVulnerable[E_W]);
    QCOMPARE(playerState4.getEvent(), gameEvent);

    // Compare list based attributes
    for(qint8 i = 0; i < tricks.size(); ++ i){
        for(qint8 j = 0; j < tricks[i].getCardCount(); ++ j){
            QCOMPARE(playerState4.getTricks()[i].getCard(j) == tricks[i].getCard(j), true);
        }
    }
    for(qint8 j = 0; j < playerHand.getCardCount(); ++ j)
        QCOMPARE(playerState4.getPlayerHand().getCard(j) == playerHand.getCard(j), true);

    for(qint8 j = 0; j < dummyHand.getCardCount(); ++ j)
        QCOMPARE(playerState4.getDummyHand().getCard(j) == dummyHand.getCard(j), true);

    for(qint8 position = NORTH; position <= WEST; ++ position){
        QCOMPARE(playerState4.getPlayerName(PlayerPosition(position)),
                 playerPositions.value(PlayerPosition(position)));
    }
}
