#include "playerstub.h"
#include <QTest>

// Default constructor
PlayerStub::PlayerStub(QObject *parent): Player(parent) {}

// Indicate to the player it is their turn to bid
void PlayerStub::notifyBidTurn()
{
    // Initialise test bids
    Bid bid1(position, CLUBS, 1);
    Bid bid2(position, DIAMONDS, 2);
    Bid bid3(position, DIAMONDS, 1);
    Bid bid5(position, PASS);

    // Make bids based on current bid
    if(gameState.getCurrentBid() == nullptr)
        emit bidSelected(bid1);
    else if(*gameState.getCurrentBid() == bid1)
        emit bidSelected(bid2);
    else if(*gameState.getCurrentBid() == bid2)
        emit bidSelected(bid3);
    else{
        // Check that the notifyBidRejected function was executed
        QCOMPARE(Bid(position, SPADES, 2), *gameState.getCurrentBid());
        emit bidSelected(bid5);
    }
}

// Indicate to the player it is their turn to play a card
void PlayerStub::notifyMoveTurn()
{
    // Check if card needs to be played from dummy hand
    CardSet hand;
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        hand = gameState.getDummyHand();
    else
        hand = gameState.getPlayerHand();

    // Check card position is not out of range
    if(playCardPos >= hand.getCardCount())
        playCardPos = 0;

    emit moveSelected(hand.getCard(playCardPos));
}

// Send the latest available game state tailored to the player
void PlayerStub::updateGameState(PlayerGameState gameState)
{
    QCOMPARE(gameState.getPlayerName(position), playerName);
    this->gameState = gameState;
}

// Indicate to the player that the last bid was rejected to the given reason
void PlayerStub::notifyBidRejected(QString reason)
{
    // Check correct reason was received from the game server
    QCOMPARE(reason, "Invalid Bid");

    Bid bid4(position, SPADES, 2);
    emit bidSelected(bid4);
}

// Indicate to the player that the last move was invalid for the given reason
void PlayerStub::notifyMoveRejected(QString reason)
{
    // Check the correct reason was received from the game server
    QCOMPARE(reason, "Invalid Card");

    // Check if card needs to be played from dummy hand
    CardSet hand;
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        hand = gameState.getDummyHand();
    else
        hand = gameState.getPlayerHand();

    // Try another card position
    playCardPos++;
    if(playCardPos >= hand.getCardCount())
        playCardPos = 0;

    emit moveSelected(hand.getCard(playCardPos));
}

// Send message to the player where source is the player name
void PlayerStub::message(QString source, QString message) {
    QString absorbSource = source;
    QString absorbMessage = message;
}

// Indicate to the player that the game is over
void PlayerStub::gameTerminated(QString reason) {
    QString absorbReason = reason;
}
