#ifndef BIDCALL_H
#define BIDCALL_H

// Represents calls that may be made by a player for their bidding turn.
// Calls are assigned numerical values with higher valued calls considered an update to
// lower valued calls given the same suit and tricks bid
enum BidCall {
    PASS = 0,
    BID = 1,
    DOUBLE_BID = 2,
    REDOUBLE_BID = 3
};

#endif // BIDCALL_H
