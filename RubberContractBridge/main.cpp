#include "gui/entrywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    EntryWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
    //    testclientlogin testcLogin;
    //    QTest::qExec(&testcLogin);
    //    TestServerLogin testLogin;
    //    QTest::qExec(&testLogin);
    //    testLobby testlob;
    //    QTest::qExec(&testlob);
}
