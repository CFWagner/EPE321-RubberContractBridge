#include "mainwindow.h"
#include <QApplication>
//Unit test includes
#include "unit-tests/game-server/testcard.h"

int main(int argc, char *argv[])
{
//    QApplication rcbApplication(argc, argv);
//    MainWindow entryWindow;
//    entryWindow.show();
//    return rcbApplication.exec();
    TestCard testCard;
    QTest::qExec(&testCard);
}
