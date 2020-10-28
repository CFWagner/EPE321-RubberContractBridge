#ifndef TESTBIDDINGPHASE_H
#define TESTBIDDINGPHASE_H

#include "gui/bidwindow.h"
#include <QtTest/QtTest>
#include <QObject>

class testBiddingPhase : public QObject
{
    Q_OBJECT
public:
    explicit testBiddingPhase(QObject *parent = nullptr);
    ~testBiddingPhase();
private slots:
    void testBid();
signals:
    void updateGameState(PlayerGameState);
private:
    PlayerGameState playerN;
    PlayerGameState playerS;
    PlayerGameState playerE;
    PlayerGameState playerW;
    BidWindow *testBidN;
    BidWindow *testBidS;
    BidWindow *testBidE;
    BidWindow *testBidW;
    QSignalSpy *sendGS;
    QSignalSpy *receiveBidN;
    QSignalSpy *receiveBidS;
    QSignalSpy *receiveBidE;
    QSignalSpy *receiveBidW;
    Bid *bidR;
};

#endif // TESTBIDDINGPHASE_H
