#include "servergamestate.h"

// Default constructor
// Initialises all attributes to values for start of match
ServerGameState::ServerGameState() {
    phase = BIDDING;
    currentBid = nullptr;
    contractBid = nullptr;
    gameNumber = 1;
    dealNumber = 1;
    trickNumber = 0;
    teamVulnerable[N_S] = false;
    teamVulnerable[E_W] = false;
    passCount = 0;
    for(qint8 player = NORTH; player <= WEST; ++player)
        playerHands.insert(PlayerPosition(player), CardSet());
}

// Update the game state based on the latest bid made
// This ServerGameState instance is responsible for the memory management of the bid argument
void ServerGameState::updateBidState(Bid* bid)
{
    // Count number of passes in a row
    if(bid->getCall() == PASS){
        ++ passCount;
        delete bid;
    }
    else if(isBidValid(currentBid, bid)){
        delete currentBid;
        currentBid = bid;
    }
    else {
        delete bid;
    }

    // Check if 4 passes have been made
    if(passCount == 4){
        // Check if bid has been made
        if(currentBid == nullptr){
            // Redeal
        }
        else{
            // Transition to play phase
        }
    }
}

// Update the game state based on the latest card played by the player
void ServerGameState::updatePlayState(PlayerPosition player, Card card)
{

}

// Update the phase of the game and attributes to indicate new phase
void ServerGameState::updatePhase(GamePhase phase)
{

}

// Setter for the player who is the dealer
void ServerGameState::setDealer(PlayerPosition player)
{
    this->dealer = dealer;
}

// Setter for the player who is the declarer
void ServerGameState::setDeclarer(PlayerPosition player)
{
    this->declarer = declarer;
}

// Getter for the cards currently in the deck
CardSet ServerGameState::getDeck()
{
    return deck;
}

// Generate and return the game state tailored for the player
PlayerGameState ServerGameState::getPlayerGameState(PlayerPosition player, QVector<Player*> players)
{
    // Create player game state here
    return PlayerGameState();
}

// Check if the new bid is valid given the current bid. Passing nullptr as the current bid
// argument implies there is no current bid
bool ServerGameState::isBidValid(const Bid* currentBid, const Bid* newBid)
{
    // Check if new bid is valid given no bid has been made yet
    if(currentBid == nullptr){
        return newBid->getCall() == PASS || newBid->getCall() == BID;
    }
    // Check if new bid is a higher bid than the current bid
    else if(*newBid > *currentBid){
        Team currentBidderTeam = getPlayerTeam(currentBid->getBidder());
        Team newBidderTeam = getPlayerTeam(newBid->getBidder());
        // Double is invalid if bid was made by a member of the same team
        if(newBid->getCall() == DOUBLE && newBidderTeam == currentBidderTeam){
            return false;
        }
        // Redouble is invalid if the bid was made by a member of the opposing team or
        // the bid was not doubled
        else if(newBid->getCall() == REDOUBLE && (newBidderTeam != currentBidderTeam
                                                  || currentBid->getCall() != DOUBLE)){
            return false;
        }
        return true;
    }
    return false;
}

Team ServerGameState::getPlayerTeam(PlayerPosition player){
    switch (player) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
    }
}
