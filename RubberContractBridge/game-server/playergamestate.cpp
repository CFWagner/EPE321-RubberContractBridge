#include "playergamestate.h"

PlayerGameState::PlayerGameState() {}

GameEvent PlayerGameState::getEvent()
{
    return gameEvent;
}

CardSet PlayerGameState::getPlayerHand()
{
    return playerHand;
}

CardSet PlayerGameState::getDummyHand()
{
    return dummyHand;
}

QString PlayerGameState::getPlayerName(PlayerPosition position)
{
    return playerPositions.value(position);
}

void PlayerGameState::read(const QJsonObject &json)
{

}

void PlayerGameState::write(QJsonObject &json) const
{

}
