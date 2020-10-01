#include "player.h"

// Default constructor
Player::Player(QObject *parent) : QObject(parent) {}

// Getter for the name of the player
QString Player::getPlayerName()
{
    return playerName;
}

// Getter for the position of the player
PlayerPosition Player::getPosition()
{
    return position;
}

// Get the team the player belongs to based on their position
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

// Setter for the position the player will play
void Player::setPosition(PlayerPosition position)
{
    this->position = position;
}
