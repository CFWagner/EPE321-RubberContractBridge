#include "gui/entrywindow.h"
#include <QApplication>

#include "unit-tests/gui/testentrywindow.h"
#include "unit-tests/gui/testserverlogin.h"
#include "unit-tests/gui/testserverlobby.h"
//Unit tests

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    // RUN Game normally
    // EntryWindow *entryWindow = new EntryWindow();

    // Unit tests
    // Entry Window
    // testEntryWindow testEW;
    // QTest::qExec(&testEW);
    // Server Login
    // testServerLogin testSLogs;
    // QTest::qExec(&testSLogs);
    // Server Lobby
    testServerLobby testSLobs;
    QTest::qExec(&testSLobs);
    return rcbApplication.exec();
}
