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
void GameServer::initializeGame()
{
    // TO DO : Randomly select dealer
    state = new ServerGameState();

    // Connect game event signal and slot
    qRegisterMetaType<GameEvent>("GameEvent");
    connect(state, SIGNAL(gameEvent(GameEvent)), this, SLOT(gameEvent(GameEvent)));

    // Send first set of state updates to players
    // TO DO: Consider waiting for ready message from players
    broadcastStateUpdate(INITIALIZE);

    // Start game by sending first turn notification
    state->startGame();
    while(true){
        bidReceived = false;
        moveReceived = false;

        notifyNextPlayerTurn();

        // Wait until player completes turn
        while(!bidReceived && !moveReceived);
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
        bidReceived = true;
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
        moveReceived = true;
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
