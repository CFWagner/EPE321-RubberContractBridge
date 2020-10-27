#include "gui/entrywindow.h"
#include <QApplication>
#include "unit-tests/game-server/testservergamestate.h"

int main(int argc, char *argv[])
{
//        QApplication rcbApplication(argc, argv);

//        EntryWindow *entryWindow = new EntryWindow();
//        entryWindow->show();

//        return rcbApplication.exec();
    TestServerGameState testServerGameState;
    QTest::qExec(&testServerGameState);
}
