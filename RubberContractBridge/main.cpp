#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Unit tests
//    TestBid testBid;
//    QTest::qExec(&testBid);
//    TestCard testCard;
//    QTest::qExec(&testCard);
//    TestCardSet testCardSet;
//    QTest::qExec(&testCardSet);
//    TestServerGameState testServerGameState;
//    QTest::qExec(&testServerGameState);
    TestPlayerGameState testPlayerGameState;
    QTest::qExec(&testPlayerGameState);
}
