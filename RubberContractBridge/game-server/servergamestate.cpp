#include "servergamestate.h"

ServerGameState::ServerGameState() {}

// Initialize all server game state attributes to values for the start of the match
void ServerGameState::initialize()
{

}

// Update the game state based on the latest bid made
void ServerGameState::updateBidState(Bid bid)
{

}

// Update the game state based on the latest card played by the player
void ServerGameState::updatePlayState(PlayerPosition player, Card card)
{

}

// Update the phase of the game
void ServerGameState::updatePhase(GamePhase phase)
{

}

// Setter for the player who is the dealer
void ServerGameState::setDealer(PlayerPosition player)
{
    this->dealer = dealer;
}

// Setter for the player who is the declarer
void ServerGameState::setDeclarer(PlayerPosition player)
{
    this->declarer = declarer;
}

// Getter for the cards currently in the deck
CardSet ServerGameState::getDeck()
{
    return deck;
}

// Generate and return the game state tailored for the player
PlayerGameState ServerGameState::getPlayerGameState(PlayerPosition player)
{
    // Create player game state here
    return PlayerGameState();
}
