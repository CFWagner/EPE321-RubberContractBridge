#include <QApplication>
#include "unit-tests/game-server/testgameserver.h"
#include "unit-tests/game-server/testserver.h"

int main(int argc, char *argv[])
{
//        QApplication rcbApplication(argc, argv);

//        EntryWindow *entryWindow = new EntryWindow();
//        entryWindow->show();

//        return rcbApplication.exec();
    TestGameServer testServer;
    QTest::qExec(&testServer);
    TestGameServer testGameServer;
    QTest::qExec(&testGameServer);
}
