#include "gameserver.h"

// Default constructor
GameServer::GameServer(QObject *parent) : QObject(parent)
{

}

// Destructor
GameServer::~GameServer()
{
    delete state;
    for(Player* player: players)
        delete player;
    players.clear();
}

// Add player to the bridge game instance
// Must be called before initialize game is called to start the game
void GameServer::addPlayer(Player* player)
{
    players.append(player);
}

// Set up and start the bridge game
void GameServer::initializeGame()
{
    // TO DO : Randomly select dealer
    state = new ServerGameState(NORTH);
    state->startGame();
}

// Slot for when a player chooses a bid for their bidding turn
void GameServer::bidSelected(Bid bid)
{
    state->updateBidState(bid);
}

// Slot for when a player selects a card for their turn
void GameServer::moveSelected(Card card)
{
    state->updatePlayState(card);
}

// Slot for when a player sends a message
void GameServer::messageGenerated(QString message)
{

}
