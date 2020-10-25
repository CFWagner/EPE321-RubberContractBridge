#include "bid.h"

// Default constructor
Bid::Bid() {}

// Constructor used when the player makes any call that is not BID
Bid::Bid(PlayerPosition bidder, BidCall call)
{
    this->bidder = bidder;
    this->call = call;
}

// Constructor used when the player makes a call that is a BID
Bid::Bid(PlayerPosition bidder, CardSuit trumpSuit, qint8 tricksAbove)
{
    this->call = BID;
    this->bidder = bidder;
    this->trumpSuit = trumpSuit;
    this->tricksAbove = tricksAbove;
}

// Getter for the position of the player who made the call
PlayerPosition Bid::getBidder() const
{
    return bidder;
}

// Getter for the call made by the player
BidCall Bid::getCall() const
{
    return call;
}

// Getter for the trump suit suggested in the bid
CardSuit Bid::getTrumpSuit() const
{
    return trumpSuit;
}

// Get the team the bidder belongs to based on their position
Team Bid::getBiddingTeam() const
{
    switch (bidder) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
    }
}

// Getter for the number of tricks above 6 selected in the bid
qint8 Bid::getTricksAbove() const
{
    return tricksAbove;
}

// Setter for the bid call
void Bid::setCall(BidCall call){
    this->call = call;
}

// Initialize bid attributes from JSON object
void Bid::read(const QJsonObject &json)
{
    bidder = PlayerPosition(json["bidder"].toInt());
    call = BidCall(json["call"].toInt());
    trumpSuit = CardSuit(json["trumpSuit"].toInt());
    tricksAbove = json["tricksAbove"].toInt();
}

// Add Bid instance attributes to the JSON object argument
void Bid::write(QJsonObject &json) const
{
    json["bidder"] = bidder;
    json["call"] = call;
    json["trumpSuit"] = trumpSuit;
    json["tricksAbove"] = tricksAbove;
}

// Overloaded > relational operator. Returns true if bid argument has lower tricks above
// or if the bid argument has a lower valued suit rank bid when the tricks above are the same.
// If the tricks and trump suit are the same, the function returns true if the bid call of
// the current bid instance is an update to the bid argumemt as defined in the BidCall enum
bool Bid::operator >(const Bid& bid) const
{
    if(tricksAbove == bid.tricksAbove){
        if(trumpSuit == bid.trumpSuit)
            return call > bid.call;
        return trumpSuit > bid.trumpSuit;
    }
    return tricksAbove > bid.tricksAbove;
}

// Overloaded == relational operator. Does not consider bidder when testing for equality
bool Bid::operator ==(const Bid& bid) const
{
    if(call == PASS && bid.call == PASS){
        return true;
    }
    else if(call == bid.call && trumpSuit == bid.trumpSuit
            && tricksAbove == bid.tricksAbove){
        return true;
    }
    return false;
}
