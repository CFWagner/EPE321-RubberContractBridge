#include "mainwindow.h"
#include <QApplication>
//Unit test includes
#include "unit-tests/game-server/testcard.h"
#include "unit-tests/game-server/testbid.h"
#include "unit-tests/game-server/testcardset.h"

int main(int argc, char *argv[])
{
//    QApplication rcbApplication(argc, argv);
//    MainWindow entryWindow;
//    entryWindow.show();
//    return rcbApplication.exec();
    TestCard testCard;
    QTest::qExec(&testCard);
//    TestBid testBid;
//    QTest::qExec(&testBid);
//    TestCardSet testCardSet;
//    QTest::qExec(&testCardSet);
}
