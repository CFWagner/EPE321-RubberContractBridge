#ifndef BID_H
#define BID_H

#include "enumerations/BidCall.h"
#include "enumerations/CardSuit.h"
#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include <QJsonObject>
#include <QtGlobal>
#include <optional>

// Represents a bid made by a player during the bidding phase
class Bid
{
public:
    Bid();
    Bid(PlayerPosition bidder, BidCall call);
    Bid(PlayerPosition bidder, CardSuit trumpSuit, qint8 tricksAbove);
    PlayerPosition getBidder() const;
    BidCall getCall() const;
    CardSuit getTrumpSuit() const;
    qint8 getTricksAbove() const;
    Team getBiddingTeam() const;
    void setCall(BidCall call);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator >(const Bid& bid) const;
    bool operator ==(const Bid& bid) const;
    PlayerPosition bidder; // Position of the player that made the bid
private:
    BidCall call; // Call made by the player during their bidding turn
    CardSuit trumpSuit; // Suit bid as trump suit. Only relevant if call is BID
    qint8 tricksAbove; // Number of tricks bid. Only relevant if call is BID
};
Q_DECLARE_METATYPE(Bid);

#endif // BID_H
