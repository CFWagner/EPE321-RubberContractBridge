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
PlayerPosition Bid::getBidder()
{
    return bidder;
}

// Getter for the call made by the player
BidCall Bid::getCall()
{
    return call;
}

// Getter for the trump suit suggested in the bid
CardSuit Bid::getTrumpSuit()
{
    return trumpSuit;
}

// Getter for the number of tricks above 6 selected in the bid
qint8 Bid::getTricksAbove()
{
    return tricksAbove;
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
