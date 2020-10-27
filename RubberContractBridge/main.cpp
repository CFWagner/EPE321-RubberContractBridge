#include <QApplication>
#include "unit-tests/game-server/testplayergamestate.h"
#include "unit-tests/game-server/testservergamestate.h"

int main(int argc, char *argv[])
{
//        QApplication rcbApplication(argc, argv);

//        EntryWindow *entryWindow = new EntryWindow();
//        entryWindow->show();

//        return rcbApplication.exec();
    TestPlayerGameState testPlayerGameState;
    QTest::qExec(&testPlayerGameState);
    TestServerGameState testServerGameState;
    QTest::qExec(&testServerGameState);
}
