#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include "hover.h"
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <QHostAddress>

namespace Ui {
class clientLogin;
}

class clientLogin : public QWidget
{
    Q_OBJECT

public:
    explicit clientLogin(QWidget *parent = nullptr);
    ~clientLogin();
    // Window is created such as the background and labels.
    void windowSetup();
    //initiate the handover to the network for connection.
    void attemptLogin();

private slots:
    //Button actions
    void on_loginButton_clicked();
    void on_infoButton_clicked();
signals:
    //A signal that sends all the details of the clients login attempt.
    void connectToServer(QHostAddress ipAddress,quint16 portID, QString username, QString password);
private:
    Ui::clientLogin *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    QString username;
};

#endif // CLIENTLOGIN_H
