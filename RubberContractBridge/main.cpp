#include "gui/entrywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication rcbApplication(argc, argv);
    EntryWindow entryWindow;
    entryWindow.show();
    return rcbApplication.exec();
}
