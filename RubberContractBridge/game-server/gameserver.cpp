#include "gameserver.h"

// Default constructor
GameServer::GameServer(QObject *parent) : QObject(parent) {}

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
    state = new ServerGameState();

    // Send first set of state updates to players
    // TO DO: Consider waiting for ready message from players
    broadcastStateUpdate(INITIALIZE);

    // Start game by sending first turn notification
    state->startGame();
    getPlayerTurn()->notifyBidTurn();
}

// Send game state updates due to the specified gameEvent tailored to each player
void GameServer::broadcastStateUpdate(GameEvent gameEvent)
{
    for(Player* player: players){
        PlayerGameState playerState = state->getPlayerGameState(player->getPosition(), players, gameEvent);
        player->updateGameState(playerState);
    }
}

// Get the player instance in the specified position
Player* GameServer::getPlayerInPosition(PlayerPosition position)
{
    for(Player* player: players){
        if(player->getPosition() == position)
            return player;
    }
    return nullptr;
}

// Get the player instance whose turn it is to play
Player* GameServer::getPlayerTurn()
{
    return getPlayerInPosition(state->getPlayerTurn());
}

// Slot for when the server game state indicates a game event has occured
void GameServer::gameEvent(GameEvent gameEvent)
{
    switch(gameEvent){
    case BID_START:
    case BID_RESTART:
    case PLAYER_BID:
    case BID_END:
    case PLAY_START:
    case TRICK_START:
    case PLAYER_MOVED:
    case TRICK_END:
    case PLAY_END:
        broadcastStateUpdate(gameEvent);
        break;
    case INITIALIZE:
    case MATCH_END:
    default:
        break;
    }
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
    QObject* senderObject = sender();
    Player* senderPlayer = (Player*) senderObject;
    for(Player* player: players)
        player->message(senderPlayer->getPlayerName(), message);
}
