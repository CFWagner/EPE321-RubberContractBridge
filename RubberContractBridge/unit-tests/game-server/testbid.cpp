#include "testbid.h"

// Default constructor
TestBid::TestBid(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of Bid class instance
void TestBid::testBid()
{
    // Construct Bid object with valid constructor arguments when call is not BID
    // Invalid arguments not possible due to enums.
    PlayerPosition bidder = NORTH;
    BidCall call = PASS;
    Bid bid1(bidder, call);

    // Test for correct Bid object state
    QCOMPARE(bidder, bid1.getBidder());
    QCOMPARE(call, bid1.getCall());

    // Construct Bid object with valid constructor arguments when call is BID
    // Invalid arguments not possible due to enums.
    CardSuit trumpSuit = HEARTS;
    qint8 tricksAbove = 3;
    bid1 = Bid(bidder, trumpSuit, tricksAbove);

    // Test for correct Bid object state
    QCOMPARE(bidder, bid1.getBidder());
    QCOMPARE(BID, bid1.getCall());
    QCOMPARE(trumpSuit, bid1.getTrumpSuit());
    QCOMPARE(tricksAbove, bid1.getTricksAbove());

    // Generate QJsonObject instance from Bid object
    QJsonObject jsonBid;
    bid1.write(jsonBid);

    // Test that QJsonObject instance contains correct keys
    QCOMPARE(jsonBid.contains("bidder"), true);
    QCOMPARE(jsonBid.contains("call"), true);
    QCOMPARE(jsonBid.contains("trumpSuit"), true);
    QCOMPARE(jsonBid.contains("tricksAbove"), true);

    // Test that correct values are present in QJsonObject instance
    QCOMPARE(jsonBid.value("bidder") == bidder, true);
    QCOMPARE(jsonBid.value("call") == BID, true);
    QCOMPARE(jsonBid.value("trumpSuit") == trumpSuit, true);
    QCOMPARE(jsonBid.value("tricksAbove") == tricksAbove, true);

    // Initialize Bid object using QJsonObject instance
    Bid bid2;
    bid2.read(jsonBid);

    // Test for correct Bid object state
    QCOMPARE(bidder, bid1.getBidder());
    QCOMPARE(BID, bid1.getCall());
    QCOMPARE(trumpSuit, bid1.getTrumpSuit());
    QCOMPARE(tricksAbove, bid1.getTricksAbove());
}
