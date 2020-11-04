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
        QCoreApplication::processEvents(QEventLoop::AllEvents);
        // Wait until player completes turn
        while(!turnComplete && !matchComplete)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
    }
}

// Send game state updates due to the specified gameEvent tailored to each player
void GameServer::broadcastStateUpdate(GameEvent gameEvent)
{
    for(Player* player: players){
        // TEMP DEBUG
        QString event = "";
        switch(gameEvent){
        case BID_START:
            event = "bid start";
            break;
        case BID_RESTART:
            event = "bid restart";
            break;
        case PLAYER_BID:
            event = "player bid";
            break;
        case BID_END:
            event = "bid end";
            break;
        case PLAY_START:
            event = "play start";
            break;
        case TRICK_START:
            event = "trick start";
            break;
        case PLAYER_MOVED:
            event = "player moved";
            break;
        case TRICK_END:
            event = "trick";
            break;
        case PLAY_END:
            event = "play end";
            break;
        case INITIALIZE:
            event = "initialize";
            break;
        case MATCH_END:
            event = "match end";
            break;
        }
        // END TEMP DEBUG

        qInfo() << "Broadcast: Event->" << player->getPlayerName() << " Event->" << event;

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
    qInfo() << "Notify player turn: " << playerTurn->getPlayerName();
    if(state->getPhase() == BIDDING){
        emit logGenerated("Game Server", playerTurn->getPlayerName() + " to bid");
        playerTurn->notifyBidTurn();
    }
    else{
        emit logGenerated("Game Server", playerTurn->getPlayerName() + " to play");
        playerTurn->notifyMoveTurn();
    }
}

// Slot for when the server game state indicates a game event has occured
void GameServer::gameEvent(GameEvent gameEvent)
{
    switch(gameEvent){
    case BID_START:
        broadcastStateUpdate(gameEvent);
        emit logGenerated("Game Server", "Bidding started");
        break;
    case BID_RESTART:
        broadcastStateUpdate(gameEvent);
        emit logGenerated("Game Server", "Bidding restarted");
        break;
    case PLAYER_BID:
        broadcastStateUpdate(gameEvent);
        break;
    case BID_END:
        broadcastStateUpdate(gameEvent);
        break;
    case PLAY_START:
        emit logGenerated("Game Server", "Cardplay started");
        broadcastStateUpdate(gameEvent);
        break;
    case TRICK_START:
        broadcastStateUpdate(gameEvent);
        break;
    case PLAYER_MOVED:
        broadcastStateUpdate(gameEvent);
        break;
    case TRICK_END:
        emit logGenerated("Game Server", "Trick completed");
        broadcastStateUpdate(gameEvent);
        break;
    case PLAY_END:
        emit logGenerated("Game Server", "Cardplay completed");
        broadcastStateUpdate(gameEvent);
        break;
    case INITIALIZE:
        emit logGenerated("Game Server", "Match started");
        break;
    case MATCH_END:
        emit logGenerated("Game Server", "Match completed");
        matchComplete = true;
        for(Player* player: players)
            player->gameTerminated("Match Completed");
        break;
    }
}

// Slot for when a player chooses a bid for their bidding turn
void GameServer::bidSelected(Bid bid)
{
    Player* senderPlayer = (Player*) sender();

    // Check if bid is valid
    if(state->isBidValid(bid)){
        emit logGenerated(senderPlayer->getPlayerName(), " Made bid");
        state->updateBidState(bid);
        turnComplete = true;
    }
    else{
        emit logGenerated(senderPlayer->getPlayerName(), " Tried to make invalid bid");
        senderPlayer->notifyBidRejected("Invalid Bid");
    }
}

// Slot for when a player selects a card for their turn
void GameServer::moveSelected(Card card)
{
    Player* senderPlayer = (Player*) sender();

    // Check if card is valid
    if(state->isCardValid(card)){
        emit logGenerated(senderPlayer->getPlayerName(), " Played card");
        state->updatePlayState(card);
        turnComplete = true;
    }
    else{
        emit logGenerated(senderPlayer->getPlayerName(), " Tried to play invalid card");
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

// Set the match completed variable
void GameServer::setMatchCompleted(bool matchComplete)
{
    this->matchComplete = matchComplete;
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
