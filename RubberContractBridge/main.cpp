#include "gui/entrywindow.h"
#include <QApplication>
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
