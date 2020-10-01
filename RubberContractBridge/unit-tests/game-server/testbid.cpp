#include "testbid.h"

TestBid::TestBid(QObject *parent) : QObject(parent)
{

}

void TestBid::dummy()
{
    QVERIFY(true);
}
