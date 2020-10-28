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
    qint8 tricksWon[4] = {0, 0, 0, 0};
    PlayerPosition playerTurn = NORTH;
    PlayerPosition handToPlay = NORTH;
    PlayerPosition dealer = NORTH;
    PlayerPosition declarer = NORTH;
    Score score;
    GameEvent gameEvent = PLAY_START;
    QMap<PlayerPosition, QString> playerPositions;
    QMap<PlayerPosition, qint8> playerCardCount;
    CardSet playerHand;
    CardSet dummyHand;

    // Construct PlayerGameState instance
    PlayerGameState playerState(phase, currentBid, contractBid, gameNumber, dealNumber,
                                trickNumber, tricks, tricksWon, playerTurn, handToPlay,
                                dealer, declarer, score, gameEvent, playerPositions, playerCardCount,
                                playerHand, dummyHand);

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
    QCOMPARE(playerState.getTeamVulnerable(N_S), false);
    QCOMPARE(playerState.getTeamVulnerable(E_W), false);
    QCOMPARE(playerState.getTricksWon(NORTH), tricksWon[NORTH]);
    QCOMPARE(playerState.getTricksWon(EAST), tricksWon[EAST]);
    QCOMPARE(playerState.getTricksWon(SOUTH), tricksWon[SOUTH]);
    QCOMPARE(playerState.getTricksWon(WEST), tricksWon[WEST]);
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
    QCOMPARE(playerState, playerState2);

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

    playerCardCount.insert(NORTH, 4);
    playerCardCount.insert(EAST, 4);
    playerCardCount.insert(SOUTH, 4);
    playerCardCount.insert(WEST, 4);

    currentBid = new Bid(NORTH, SPADES, 5);
    contractBid = new Bid(SOUTH, HEARTS, 2);

    // Construct PlayerGameState instance
    PlayerGameState playerState3(phase, currentBid, contractBid, gameNumber, dealNumber,
                                trickNumber, tricks, tricksWon, playerTurn, handToPlay, dealer, declarer,
                                score, gameEvent, playerPositions, playerCardCount,
                                playerHand, dummyHand);

    // Test PlayerGameState instance attributes
    QCOMPARE(playerState3.getPhase(), phase);
    QCOMPARE(*playerState3.getCurrentBid() == *currentBid, true);
    QCOMPARE(*playerState3.getContractBid() == *contractBid, true);
    QCOMPARE(playerState3.getGameNumber(), gameNumber);
    QCOMPARE(playerState3.getDealNumber(), dealNumber);
    QCOMPARE(playerState3.getTrickNumber(), trickNumber);
    QCOMPARE(playerState3.getPlayerTurn(), playerTurn);
    QCOMPARE(playerState3.getHandToPlay(), handToPlay);
    QCOMPARE(playerState3.getDealer(), dealer);
    QCOMPARE(playerState3.getDeclarer(), declarer);
    QCOMPARE(playerState3.getTeamVulnerable(N_S), false);
    QCOMPARE(playerState3.getTeamVulnerable(E_W), false);
    QCOMPARE(playerState3.getTricksWon(NORTH), tricksWon[NORTH]);
    QCOMPARE(playerState3.getTricksWon(EAST), tricksWon[EAST]);
    QCOMPARE(playerState3.getTricksWon(SOUTH), tricksWon[SOUTH]);
    QCOMPARE(playerState3.getTricksWon(WEST), tricksWon[WEST]);
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
    playerState3.write(jsonPlayerState3);
    PlayerGameState playerState4;
    playerState4.read(jsonPlayerState3);

    // Test target PlayerGameState instance attributes
    QCOMPARE(playerState3, playerState4);

    // Call game state copy constructor
    GameState gameState1(playerState3);

    // Test PlayerGameState instance attributes
    QCOMPARE(gameState1.getPhase(), playerState3.getPhase());
    QCOMPARE(*gameState1.getCurrentBid() == *playerState3.getCurrentBid(), true);
    QCOMPARE(*gameState1.getContractBid() == *playerState3.getContractBid(), true);
    QCOMPARE(gameState1.getGameNumber(), playerState3.getGameNumber());
    QCOMPARE(gameState1.getDealNumber(), playerState3.getDealNumber());
    QCOMPARE(gameState1.getTrickNumber(), playerState3.getTrickNumber());
    QCOMPARE(gameState1.getPlayerTurn(), playerState3.getPlayerTurn());
    QCOMPARE(gameState1.getHandToPlay(), playerState3.getHandToPlay());
    QCOMPARE(gameState1.getDealer(), playerState3.getDealer());
    QCOMPARE(gameState1.getDeclarer(), playerState3.getDeclarer());
    QCOMPARE(gameState1.getTeamVulnerable(N_S), playerState3.getTeamVulnerable(N_S));
    QCOMPARE(gameState1.getTeamVulnerable(E_W), playerState3.getTeamVulnerable(E_W));
    QCOMPARE(gameState1.getTricksWon(N_S), playerState3.getTricksWon(N_S));
    QCOMPARE(gameState1.getTricksWon(E_W), playerState3.getTricksWon(E_W));
    QCOMPARE(gameState1.getTricksWon(NORTH), playerState3.getTricksWon(NORTH));
    QCOMPARE(gameState1.getTricksWon(EAST), playerState3.getTricksWon(EAST));
    QCOMPARE(gameState1.getTricksWon(SOUTH), playerState3.getTricksWon(SOUTH));
    QCOMPARE(gameState1.getTricksWon(WEST), playerState3.getTricksWon(WEST));

    // Compare list based attributes
    for(qint8 i = 0; i < tricks.size(); ++ i){
        for(qint8 j = 0; j < tricks[i].getCardCount(); ++ j){
            QCOMPARE(gameState1.getTricks()[i].getCard(j) == playerState3.getTricks()[i].getCard(j), true);
        }
    }

    delete currentBid;
    delete contractBid;
}
