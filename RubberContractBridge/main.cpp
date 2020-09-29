#include "mainwindow.h"
#include "clientgui.h"
#include "servergui.h"
#include "logger.h"
#include "testlogger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Test logger class
    //testLog.log(QString("This is context"),QString("This is the message"));
    // Test logger class
    testLogger test1;
    QTest::qExec(&test1);

    //
    QApplication rcbApplication(argc, argv);
    MainWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
