#include "mainwindow.h"
#include "clientgui.h"
#include "servergui.h"
#include "logger.h"
#include "testlogger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    MainWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
