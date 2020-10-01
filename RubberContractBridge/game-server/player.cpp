#include "player.h"

Player::Player(QObject *parent) : QObject(parent) {}

QString Player::getPlayerName()
{
    return playerName;
}

PlayerPosition Player::getPosition()
{
    return position;
}

Team Player::getTeam()
{
    switch (position) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
    }
}

void Player::setPosition(PlayerPosition position)
{
    this->position = position;
}

QString Player::toString()
{
    return "";
}
