#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include "hover.h"
#include "serverlogin.h"
#include "clientlogin.h"
#include <QWidget>
#include <QDebug>

namespace Ui {
class EntryWindow;
}

class EntryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    // All windows are created in 2 steps: setup of the window view and
    // creating all foreground elements such as buttons.
    void setupWindow();
    void staticGUIElements();
    int getPageID();
    ServerLogin *serverLogin;
    ClientLogin *clientLogin;

    //The slots are used to move from the Entry window to the login windows.
public slots:
    void goServerLogin();
    void goClientLogin();

    //Each window has a pageID and pointers of their next possible window.
private:
    Ui::EntryWindow *ui;
    int pageID = 0;
};

#endif // ENTRYWINDOW_H
