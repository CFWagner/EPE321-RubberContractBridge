#include "bid.h"

Bid::Bid()
{

}

Bid::Bid(PlayerPosition bidder, BidCall call)
{
    this->bidder = bidder;
    this->call = call;
}

Bid::Bid(PlayerPosition bidder, CardSuit trumpSuit, qint8 tricksAbove)
{
    this->call = BID;
    this->bidder = bidder;
    this->trumpSuit = trumpSuit;
    this->tricksAbove = tricksAbove;
}

PlayerPosition Bid::getBidder()
{
    return bidder;
}

BidCall Bid::getCall()
{
    return call;
}

CardSuit Bid::getTrumpSuit()
{
    return trumpSuit;
}

qint8 Bid::getTricksAbove()
{
    return tricksAbove;
}

void Bid::read(const QJsonObject &json)
{

}

void Bid::write(const QJsonObject &json)
{

}

QString Bid::toString()
{
    return "";
}
