#include "gui/entrywindow.h"
#include <QApplication>
//Unit tests

int main(int argc, char *argv[])
{
        QApplication rcbApplication(argc, argv);

        EntryWindow *entryWindow = new EntryWindow();
        entryWindow->show();

        return rcbApplication.exec();
}
