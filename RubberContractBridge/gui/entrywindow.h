#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H
#include "servergui.h"
#include "clientlogin.h"
#include <QHostAddress>
#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class EntryWindow;
}

class EntryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    // Window is created such as the background and labels.
    void windowSetup();

private:
    Ui::EntryWindow *ui;
    QPushButton *clientButton;
    QPushButton *serverButton;
    ServerGUI * serverLogin;
    clientLogin *loginWindow;
private slots:
    void on_clientButton_clicked();
    void on_serverButton_clicked();
};

#endif // ENTRYWINDOW_H
