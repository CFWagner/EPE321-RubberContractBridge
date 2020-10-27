#include "player.h"

// Default constructor
Player::Player(QObject *parent) : QObject(parent) {}

// Getter for the name of the player
QString Player::getPlayerName() const
{
    return playerName;
}

// Getter for the position of the player
PlayerPosition Player::getPosition() const
{
    return position;
}

// Get the team the player belongs to based on their position
Team Player::getTeam() const
{
    switch (position) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
    }
}

// Setter for the player name
void Player::setPlayerName(QString playerName)
{
    this->playerName = playerName;
}

// Setter for the position the player will play
void Player::setPosition(PlayerPosition position)
{
    this->position = position;
}
