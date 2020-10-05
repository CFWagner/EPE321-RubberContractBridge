#include "servergamestate.h"

// Default constructor
// Initialises all attributes to values for start of match
ServerGameState::ServerGameState()
{
    // Initialise attributes
    phase = BIDDING;
    currentBid = nullptr;
    contractBid = nullptr;
    gameNumber =0;
    dealNumber = 0;
    trickNumber = 0;
    teamVulnerable[N_S] = false;
    teamVulnerable[E_W] = false;
    passCount = 0;
    dealer = NORTH;

    // Initialise player hands
    for(qint8 player = NORTH; player <= WEST; ++player)
        playerHands.insert(PlayerPosition(player), CardSet());

    // Populate card set with all of the 52 different cards
    for(qint8 suitVal = CLUBS; suitVal <= SPADES; suitVal++){
        CardSuit suit = CardSuit(suitVal);
        for(qint8 rankVal = ACE; rankVal <= KING; rankVal++){
            CardRank rank = CardRank(rankVal);
            Card card(suit, rank);
            deck.addCard(card);
        }
    }
}

// Prepare game for next deal round
// Reset game specific attributes, shuffle deck and deal cards
void ServerGameState::nextDeal()
{
    // Select player to left of current dealer as new dealer
    dealer = PlayerPosition((dealer + 1) % 4);

    // Reset attributes
    phase = BIDDING;
    currentBid = nullptr;
    contractBid = nullptr;
    ++ dealNumber;
    trickNumber = 0;
    tricks.clear();
    passCount = 0;

    // Clear player hands
    for(qint8 player = NORTH; player <= WEST; ++ player)
        playerHands[PlayerPosition(player)].clearSet();

    // Shuffle deck
    deck.shuffle();

    // Deal cards in clockwise direction
    // Select player to dealer's left as first player to receive a card
    PlayerPosition targetPlayer = PlayerPosition((dealer + 1) % 4);
    while(deck.getCardCount() > 0){
        playerHands[targetPlayer].addCard(deck.removeTopCard());
    }

    // Select player to left of dealer for first turn
    playerTurn = PlayerPosition((dealer + 1) % 4);
}

// Prepare game for next trick
void ServerGameState::nextTrick()
{
    ++ trickNumber;
    tricks.append(CardSet());
}


// Update the game state based on the latest bid made
// This ServerGameState instance is responsible for the memory management of the bid argument
// Does nothing if the bid is invalid. Bid validity must be checked seperately prior to
// calling this function isBidValid()
void ServerGameState::updateBidState(Bid* bid)
{
    // Count number of passes in a row
    if(bid->getCall() == PASS){
        ++ passCount;
        delete bid;
    }
    else if(isBidValid(bid)){
        delete currentBid;
        currentBid = bid;
    }
    else {
        delete bid;
        return;
    }

    // Select player to left of most recent player to play for next turn
    playerTurn = PlayerPosition((playerTurn + 1) % 4);

    // Check if 4 passes have been made
    if(passCount == 4){
        // Check if bid has been made
        if(currentBid == nullptr){
            // Redeal cards
            nextDeal();
        }
        else{
            // Transition to play phase
            phase = CARDPLAY;
            contractBid = currentBid;
            currentBid = nullptr;
            declarer = contractBid->getBidder();
            // Select player to left of declarer for first turn
            playerTurn = PlayerPosition((declarer + 1) % 4);
            handToPlay = playerTurn;
            nextTrick();
        }
    }
}

// Update the game state based on the latest card played by the player
// Assumes card is played from handToPlay by the PlayerTurn player
// Does nothing if the bid is invalid. Card validity must be checked seperately prior to
// calling this function using isCardValid()
void ServerGameState::updatePlayState(Card card)
{
    // Check if card played is valid
    if(!isCardValid(card))
        return;

    // Play card
    CardSet* currentTrick = &tricks[trickNumber - 1];
    currentTrick->addCard(card);

    // Check if trick is complete
    if(currentTrick->getCardCount() == 4){

    }
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
bool ServerGameState::isBidValid(const Bid* bid)
{
    // Check if new bid is valid given no bid has been made yet
    if(currentBid == nullptr){
        return bid->getCall() == PASS || bid->getCall() == BID;
    }
    // Check if new bid is a higher bid than the current bid
    else if(*bid > *currentBid){
        Team currentBidderTeam = getPlayerTeam(currentBid->getBidder());
        Team newBidderTeam = getPlayerTeam(bid->getBidder());
        // Double is invalid if bid was made by a member of the same team
        if(bid->getCall() == DOUBLE && newBidderTeam == currentBidderTeam){
            return false;
        }
        // Redouble is invalid if the bid was made by a member of the opposing team or
        // the bid was not doubled
        else if(bid->getCall() == REDOUBLE && (newBidderTeam != currentBidderTeam
                                                  || currentBid->getCall() != DOUBLE)){
            return false;
        }
        return true;
    }
    return false;
}

// Check if the card is valid to play in the current trick. Assumes the card is played from
// the hand indicated by handToPlay
bool ServerGameState::isCardValid(const Card card)
{
    // Check if card is in hand to play
    if(!playerHands[handToPlay].containsCard(card))
        return false;

    // Check if any cards have been played in the current trick
    CardSet trick = tricks[trickNumber - 1];
    if(trick.getCardCount() == 0)
        return true;

    // Check if the card is of the trump suit or matches the suit of the first card played
    // in the trick
    if(card.getSuit() == contractBid->getTrumpSuit()
            || card.getSuit() == trick.getCard(0).getSuit()){
        return true;
    }
    return false;
}

// Get the team the player belongs to based on their position
Team ServerGameState::getPlayerTeam(PlayerPosition player){
    switch (player) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
    }
}
