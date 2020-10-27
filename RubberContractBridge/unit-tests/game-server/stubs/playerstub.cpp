#include "playerstub.h"

// Default constructor
PlayerStub::PlayerStub(QObject *parent): Player(parent) {}

// Indicate to the player it is their turn to bid
void PlayerStub::notifyBidTurn()
{
    // Initialise test bids
    Bid bid1(position, CLUBS, 1);
    Bid bid2(position, SPADES, 2);
    Bid bid3(position, PASS);

    // Make bids based on current bid
    if(gameState.getCurrentBid() == nullptr)
        emit bidSelected(bid1);
    else if(*gameState.getCurrentBid() == bid1)
        emit bidSelected(bid2);
    else
        emit bidSelected(bid3);
}

// Indicate to the player it is their turn to play a card
void PlayerStub::notifyMoveTurn()
{
    if(playCardPos >= gameState.getPlayerHand().getCardCount())
        playCardPos = 0;

    // Check if card needs to be played from dummy hand
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        emit moveSelected(gameState.getDummyHand().getCard(playCardPos));
    else
        emit moveSelected(gameState.getPlayerHand().getCard(playCardPos));
}

// Send the latest available game state tailored to the player
void PlayerStub::updateGameState(PlayerGameState gameState)
{
    this->gameState = gameState;
}

// Indicate to the player that the last bid was rejected to the given reason
void PlayerStub::notifyBidRejected(QString reason)
{

}

// Indicate to the player that the last move was invalid for the given reason
void PlayerStub::notifyMoveRejected(QString reason)
{
    // Try another card position
    playCardPos++;
    if(playCardPos >= gameState.getPlayerHand().getCardCount())
        playCardPos = 0;

    // Check if card needs to be played from dummy hand
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        emit moveSelected(gameState.getDummyHand().getCard(playCardPos));
    else
        emit moveSelected(gameState.getPlayerHand().getCard(playCardPos));
}

// Send message to the player where source is the player name
void PlayerStub::message(QString source, QString message)
{

}

// Indicate to the player that the game is over
void PlayerStub::gameTerminated(QString reason)
{

}
