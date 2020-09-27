#include "mainwindow.h"
#include "clientgui.h"
#include "servergui.h"
#include "logger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Test logger class
    Logger testLog;


    //
    QApplication rcbApplication(argc, argv);
    MainWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
