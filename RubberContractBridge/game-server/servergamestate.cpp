#include "servergamestate.h"

ServerGameState::ServerGameState() {}

void ServerGameState::initialize()
{

}

void ServerGameState::updateBidState(Bid bid)
{

}

void ServerGameState::updatePlayState(PlayerPosition player, Card card)
{

}

void ServerGameState::updatePhase(GamePhase phase)
{

}

void ServerGameState::setDealer(PlayerPosition player)
{
    this->dealer = dealer;
}

void ServerGameState::setDeclarer(PlayerPosition player)
{
    this->declarer = declarer;
}

CardSet ServerGameState::getDeck()
{
    return deck;
}

PlayerGameState ServerGameState::getPlayerGameState()
{
    // Create player game state here
    return PlayerGameState();
}

void ServerGameState::read(const QJsonObject &json)
{

}

void ServerGameState::write(QJsonObject &json) const
{

}
