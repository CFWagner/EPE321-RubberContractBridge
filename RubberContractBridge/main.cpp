#include "gui/mainwindow.h"
#include <QApplication>
//Unit tests
#include "unit-tests/game-server/testservergamestate.h"
#include "unit-tests/game-server/testplayergamestate.h"

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    MainWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
//Unit tests
// Test the main class
//    TestServerGameState testServerGameState;
//    QTest::qExec(&testServerGameState);
//    TestPlayerGameState testPlayerGameState;
//    QTest::qExec(&testPlayerGameState);
}
