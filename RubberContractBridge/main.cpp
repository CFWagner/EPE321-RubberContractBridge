#include "gui/entrywindow.h"
#include "unit-tests/gui/testserverlogin.h"
#include "unit-tests/gui/testclientlogin.h"
#include "unit-tests/gui/testlobby.h"
#include <QApplication>
//Unit tests

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
//    EntryWindow entryWindow;
//    entryWindow.show();
//    TestServerLogin testLogin;
//    QTest::qExec(&testLogin);
//    testclientlogin testcLogin;
//    QTest::qExec(&testcLogin);
    testLobby testlob;
    QTest::qExec(&testlob);
    return rcbApplication.exec();
}
