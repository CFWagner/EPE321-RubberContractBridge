#include "gui/entrywindow.h"
#include <QApplication>
#include <QTest>
#include "unit-tests/game-server/testgameserver.h"

int main(int argc, char *argv[])
{
//    TestPlayerGameState testPlayerGameState;
//    QTest::qExec(&testPlayerGameState);
    QApplication rcbApplication(argc, argv);
    EntryWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
