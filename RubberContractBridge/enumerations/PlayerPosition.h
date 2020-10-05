#ifndef PLAYERPOSITION_H
#define PLAYERPOSITION_H

// Represents the position of a player in the game
// Players are ordered according to the direction of play (i.e. clockwise around table)
enum PlayerPosition{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

#endif // PLAYERPOSITION_H
