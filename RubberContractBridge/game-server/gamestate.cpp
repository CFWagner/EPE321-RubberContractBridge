#include "gamestate.h"

// Default constructor
GameState::GameState() {}

// Copy constructor
GameState::GameState(const GameState &gameState)
{
    this->phase = gameState.phase;
    if(gameState.getCurrentBid() == nullptr)
        currentBid = nullptr;
    else
        currentBid = new Bid(*gameState.getCurrentBid());
    if(gameState.getContractBid() == nullptr)
        contractBid = nullptr;
    else
        contractBid = new Bid(*gameState.getContractBid());
    this->gameNumber = gameState.gameNumber;
    this->dealNumber = gameState.dealNumber;
    this->trickNumber = gameState.trickNumber;
    this->tricks = gameState.tricks;
    this->playerTurn = gameState.playerTurn;
    this->handToPlay = gameState.handToPlay;
    this->dealer = gameState.dealer;
    this->declarer = gameState.declarer;
    this->score = gameState.score;
}

// Copy assignment operator
GameState& GameState::operator = (const GameState &gameState)
{
    this->phase = gameState.phase;
    this->currentBid = new Bid(*gameState.currentBid);
    this->contractBid = new Bid(*gameState.contractBid);
    this->gameNumber = gameState.gameNumber;
    this->dealNumber = gameState.dealNumber;
    this->trickNumber = gameState.trickNumber;
    this->tricks = gameState.tricks;
    this->playerTurn = gameState.playerTurn;
    this->handToPlay = gameState.handToPlay;
    this->dealer = gameState.dealer;
    this->declarer = gameState.declarer;
    this->score = gameState.score;
    return *this;
}

// Destructor
GameState::~GameState() {
    delete currentBid;
    delete contractBid;
}

// Getter for the current game phase
GamePhase GameState::getPhase() const
{
    return phase;
}

// Getter for the lasest standing bid made. Returns nullptr is there is no current bid
const Bid* GameState::getCurrentBid() const
{
    return currentBid;
}


// Getter for the bid selected as the contract. Returns nullptr is there is no contract bid
const Bid* GameState::getContractBid() const
{
    return contractBid;
}

// Getter for the current game number
qint8 GameState::getGameNumber() const
{
    return gameNumber;
}

// Getter for the current deal number
qint8 GameState::getDealNumber() const
{
    return dealNumber;
}

// Getter for the current trick number
qint8 GameState::getTrickNumber() const
{
    return trickNumber;
}

// Getter for the set of tricks that have been played so far in the current game.
// The element at index 0 is the first trick played and the last element is the latest trick
// The element at index 0 in the card set is the first card played in the trick and the last
// element is the last card played in the trick
const QVector<CardSet> GameState::getTricks() const
{
    return tricks;
}

// Getter for the player who's turn it is to play. The turn refers to which player is called
// to action. For example, when a card is to be played from the dummy's hand, this returns
// the player that is the declarer as action is required from them.
PlayerPosition GameState::getPlayerTurn() const
{
    return playerTurn;
}

// Getter for the player who's hand it is to play. The hand refers to which player's hand a
// card must be played onto the trick from. For example, when a card is to be played from the
// dummy's hand by the declarer, this returns the player that is the dummy as it is there hand
// that a card must be played from.
PlayerPosition GameState::getHandToPlay() const
{
    return handToPlay;
}

// Getter for the player that is the dealer
PlayerPosition GameState::getDealer() const
{
    return dealer;
}

// Getter for the player that is the declarer
PlayerPosition GameState::getDeclarer() const
{
    return declarer;
}

// Getter for the player that is the dummy
PlayerPosition GameState::getDummy() const
{
    switch (declarer) {
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case EAST:
            return WEST;
        case WEST:
        default:
            return EAST;

    }
}

// Returns whether the specified team is in the vulnerable state
bool GameState::getTeamVulnerable(Team team) const
{
    return score.getTeamVulnerable(team);
}

// Getter for the score for the current match
Score GameState::getScore() const
{
    return score;
}
