#include "gui/entrywindow.h"
#include "gui/bidwindow.h"
#include <QApplication>
#include "unit-tests/game-server/testgameserver.h"
#include "unit-tests/game-server/testserver.h"

#include "unit-tests/gui/testentrywindow.h"
#include "unit-tests/gui/testserverlogin.h"
#include "unit-tests/gui/testserverlobby.h"
#include "unit-tests/gui/testclientlogin.h"
#include "unit-tests/gui/testbiddingphase.h"
//Unit tests

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    // RUN Game normally
    //BidWindow *bidwindow = new BidWindow();

    // Unit tests
    // Entry Window
    testEntryWindow testEW;
    QTest::qExec(&testEW);
    // Server Login
    testServerLogin testSLogs;
    QTest::qExec(&testSLogs);
    // Server Lobby
    testServerLobby testSLobs;
    QTest::qExec(&testSLobs);
    // Client Lobby
    testClientLogin testCLogs;
    QTest::qExec(&testCLogs);
    // Bidding phase
    testBiddingPhase testBids;
    QTest::qExec(&testBids);
    return rcbApplication.exec();
}
