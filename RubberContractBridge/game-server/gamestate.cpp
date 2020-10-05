#include "gamestate.h"

GameState::GameState() {}

GamePhase GameState::getPhase()
{
    return phase;
}

Bid GameState::getCurrentBid()
{
    return currentBid;
}

Bid GameState::getContractBid()
{
    return contractBid;
}

qint8 GameState::getGameNumber()
{
    return gameNumber;
}

qint8 GameState::getDealNumber()
{
    return dealNumber;
}

qint8 GameState::getTrickNumber()
{
    return trickNumber;
}

QVector<CardSet> GameState::getTricks()
{
    return tricks;
}

PlayerPosition GameState::getPlayerTurn()
{
    return playerTurn;
}

PlayerPosition GameState::getHandToPlay()
{
    return handToPlay;
}

PlayerPosition GameState::getDealer()
{
    return dealer;
}

PlayerPosition GameState::getDeclarer()
{
    return declarer;
}

PlayerPosition GameState::getDummy()
{
    switch (declarer) {
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case EAST:
            return WEST;
        case WEST:
            return EAST;
    }
}

bool GameState::getTeamVulnerable(Team team)
{
    return teamVulnerable[team];
}

Score GameState::getScore()
{
    return score;
}
