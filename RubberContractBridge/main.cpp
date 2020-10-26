#include "gui/entrywindow.h"
#include <QApplication>
#include <unit-tests/game-server/testbid.h>
#include <unit-tests/game-server/testcard.h>
#include <unit-tests/game-server/testcardset.h>
#include <unit-tests/game-server/testplayergamestate.h>
#include <unit-tests/game-server/testservergamestate.h>
#include <unit-tests/game-server/testscore.h>
//Unit tests

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    EntryWindow entryWindow;
    entryWindow.show();
    //    testclientlogin testcLogin;
    //    QTest::qExec(&testcLogin);
    //    TestServerLogin testLogin;
    //    QTest::qExec(&testLogin);
    //    testLobby testlob;
    //    QTest::qExec(&testlob);
    return rcbApplication.exec();
}
