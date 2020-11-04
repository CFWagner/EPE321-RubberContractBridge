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
void GameServer::executeMatch(qint32 maxRubbers, bool verboseOutput)
{
    this->verboseOutput = verboseOutput;
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
        if(verboseOutput)
            emit logGenerated("Game Server", playerTurn->getPlayerName() + " to bid");
        playerTurn->notifyBidTurn();
    }
    else{
        if(verboseOutput)
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
        if(verboseOutput)
            emit logGenerated("Game Server", "Bidding started");
        break;
    case BID_RESTART:
        broadcastStateUpdate(gameEvent);
        if(verboseOutput)
            emit logGenerated("Game Server", "Bidding restarted");
        break;
    case PLAYER_BID:
        broadcastStateUpdate(gameEvent);
        break;
    case BID_END:
        broadcastStateUpdate(gameEvent);
        break;
    case PLAY_START:
        if(verboseOutput)
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
        if(verboseOutput)
            emit logGenerated("Game Server", "Trick " + QString::number(state->getTrickNumber()) + "completed");
        broadcastStateUpdate(gameEvent);
        break;
    case PLAY_END:
        if(verboseOutput)
            emit logGenerated("Game Server", "Cardplay completed");
        broadcastStateUpdate(gameEvent);
        break;
    case INITIALIZE:
        emit logGenerated("Game Server", "Match started");
        break;
    case MATCH_END:
        emit logGenerated("Game Server", "Rubber " + QString::number(state->getRubberNumber()) + " completed");
        logScore();
        emit logGenerated("Game Server", "Match completed");
        logMatchWinner();
        matchComplete = true;
        for(Player* player: players)
            player->gameTerminated("Match completed");
        break;
    case RUBBER_COMPLETED:
        emit logGenerated("Game Server", "Rubber " + QString::number(state->getRubberNumber()) + " completed");
        logScore();
    }
}

// Slot for when a player chooses a bid for their bidding turn
void GameServer::bidSelected(Bid bid)
{
    Player* senderPlayer = (Player*) sender();

    // Check if bid is valid
    if(state->isBidValid(bid)){
        if(verboseOutput)
            emit logGenerated(senderPlayer->getPlayerName(), getBidInfo(bid));
        state->updateBidState(bid);
        turnComplete = true;
    }
    else{
        if(verboseOutput)
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
        if(verboseOutput)
            emit logGenerated(senderPlayer->getPlayerName(), " Played card " + getCardInfo(card));
        state->updatePlayState(card);
        turnComplete = true;
    }
    else{
        if(verboseOutput)
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

// Getter for players
const QVector<Player*> GameServer::getPlayers() const
{
    return players;
}

QString GameServer::getCardInfo(Card card)
{
    QString suit = "";
    switch(card.getSuit()){
    case CLUBS:
        suit = "CLUBS";
        break;
    case HEARTS:
        suit = "HEARTS";
        break;
    case SPADES:
        suit = "SPADES";
        break;
    case DIAMONDS:
        suit = "DIAMONDS";
        break;
    }

    QString rank = "";
    switch (card.getRank()) {
    case TWO:
        rank = "TWO";
        break;
    case THREE:
        rank = "THREE";
        break;
    case FOUR:
        rank = "FOUR";
        break;
    case FIVE:
        rank = "FIVE";
        break;
    case SIX:
        rank = "SIX";
        break;
    case SEVEN:
        rank = "SEVEN";
        break;
    case EIGHT:
        rank = "EIGHT";
        break;
    case NINE:
        rank = "NINE";
        break;
    case TEN:
        rank = "TEN";
        break;
    case JACK:
        rank = "JACK";
        break;
    case QUEEN:
        rank = "QUEEN";
        break;
    case KING:
        rank = "KING";
        break;
    case ACE:
        rank = "ACE";
        break;
    }

    return rank + " of " + suit;
}

QString GameServer::getBidInfo(Bid bid)
{
    QString suit = "";
    switch(bid.getTrumpSuit()){
    case CLUBS:
        suit = "CLUBS";
        break;
    case HEARTS:
        suit = "HEARTS";
        break;
    case SPADES:
        suit = "SPADES";
        break;
    case DIAMONDS:
        suit = "DIAMONDS";
        break;
    case NONE:
        suit = "no";
        break;
    }

    QString oddTricks = QString::number(bid.getTricksAbove());

    QString output = "";
    switch(bid.getCall()){
    case BID:
        output = "Bid " + oddTricks + " odd tricks " + suit + " trump suit";
        break;
    case DOUBLE_BID:
        output = "Doubled bid";
        break;
    case REDOUBLE_BID:
        output = "Redoubled bid";
        break;
    case PASS:
        output = "Passed on bid";
        break;
    }

    return output;
}

void GameServer::logScore()
{
    QString winningTeam;
    switch(state->getScore().getRubberWinner()){
    case N_S:
        winningTeam = "NORTH-SOUTH";
        break;
    case E_W:
        winningTeam = "EAST-WEST";
        break;
    }

    const Score& score = state->getScore();
    emit logGenerated("Score", "Winner      : " + winningTeam);
    emit logGenerated("Score", "Games Won   : NS = " + QString::number(score.getGamesWon(N_S)) + ", EW = " + QString::number(score.getGamesWon(E_W)));
    for(int i = 0; i < score.getContractPoints(N_S).size(); i++){
        emit logGenerated("Score", "Game " + QString::number(i + 1) + "  : NS = " + QString::number(score.getContractPoints(N_S).value(i)) + ", EW = " + QString::number(score.getContractPoints(E_W).value(i)));
    }
    emit logGenerated("Score", "Back Scores : NS = " + QString::number(score.getBackScore(N_S)) + ", EW = " + QString::number(score.getBackScore(E_W)));
    emit logGenerated("Score", "Total Scores: NS = " + QString::number(score.getTotalScore(N_S)) + ", EW = " + QString::number(score.getTotalScore(E_W)));
    emit logGenerated("Score", "-----------------------------------------------");
}

void GameServer::logMatchWinner()
{
    QString winningTeam;
    switch(state->getScore().getMatchWinner()){
    case N_S:
        winningTeam = "NORTH-SOUTH";
        break;
    case E_W:
        winningTeam = "EAST-WEST";
        break;
    }

    emit logGenerated("Score", "Match Winner: " + winningTeam);
}
