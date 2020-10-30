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
    connect(player, SIGNAL(bidSelected(Bid)), this, SLOT(bidSelected(Bid)));
    connect(player, SIGNAL(moveSelected(Card)), this, SLOT(moveSelected(Card)));
    connect(player, SIGNAL(messageGenerated(QString)), this, SLOT(messageGenerated(QString)));
}

// Set up and start the bridge game
void GameServer::executeMatch(qint32 maxRubbers)
{
    state = new ServerGameState();

    if(maxRubbers <= 0)
        return;

    // Connect game event signal and slot
    qRegisterMetaType<GameEvent>("GameEvent");
    connect(state, SIGNAL(gameEvent(GameEvent)), this, SLOT(gameEvent(GameEvent)));

    // Send first set of state updates to players
    // TO DO: Consider waiting for ready message from players
    broadcastStateUpdate(INITIALIZE);

    // Start match
    state->startMatch(maxRubbers);

    // Execute main game loop until match is complete
    matchComplete = false;
    while(!matchComplete){
        turnComplete = false;

        // Indicate to next player to take turn
        notifyNextPlayerTurn();

        // Wait until player completes turn
        while(!turnComplete);
    }
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
void GameServer::notifyNextPlayerTurn()
{
    Player* playerTurn = getPlayerInPosition(state->getPlayerTurn());
    if(state->getPhase() == BIDDING)
        playerTurn->notifyBidTurn();
    else
        playerTurn->notifyMoveTurn();
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
        break;
    case MATCH_END:
        matchComplete = true;
        for(Player* player: players)
            player->gameTerminated("Match Completed");
        break;
    }
}

// Slot for when a player chooses a bid for their bidding turn
void GameServer::bidSelected(Bid bid)
{
    // Check if bid is valid
    if(state->isBidValid(bid)){
        state->updateBidState(bid);
        turnComplete = true;
    }
    else{
        Player* senderPlayer = (Player*) sender();
        senderPlayer->notifyBidRejected("Invalid Bid");
    }
}

// Slot for when a player selects a card for their turn
void GameServer::moveSelected(Card card)
{
    // Check if card is valid
    if(state->isCardValid(card)){
        state->updatePlayState(card);
        turnComplete = true;
    }
    else{
        Player* senderPlayer = (Player*) sender();
        senderPlayer->notifyMoveRejected("Invalid Card");
    }
}

// Slot for when a player sends a message
void GameServer::messageGenerated(QString message)
{
    Player* senderPlayer = (Player*) sender();
    for(Player* player: players)
        player->message(senderPlayer->getPlayerName(), message);
}

// Getter for the server game state
const ServerGameState* GameServer::getState() const
{
    return state;
}

const QVector<Player*> GameServer::getPlayers() const
{
    return players;
}
