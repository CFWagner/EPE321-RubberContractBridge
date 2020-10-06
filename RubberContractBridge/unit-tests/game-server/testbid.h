#ifndef TESTBID_H
#define TESTBID_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "game-server/bid.h"

// Unit test class for Bid class
class TestBid : public QObject
{
    Q_OBJECT
public:
    explicit TestBid(QObject *parent = nullptr);

private slots:
    void testBid();

};

#endif // TESTBID_H
