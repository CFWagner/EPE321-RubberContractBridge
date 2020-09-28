#include "mainwindow.h"
#include "clientgui.h"
#include "servergui.h"
#include "logger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Test logger class
    Logger testLog;
    //testLog.log(QString("This is context"),QString("This is the message"));

    //
    QApplication rcbApplication(argc, argv);
    MainWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
