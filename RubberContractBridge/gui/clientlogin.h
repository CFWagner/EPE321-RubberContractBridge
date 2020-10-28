#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include "hover.h"
#include <QHostAddress>
#include <QWidget>
#include <QObject>

namespace Ui {
class ClientLogin;
}

class ClientLogin : public QWidget
{
    Q_OBJECT

public:
    explicit ClientLogin(QWidget *parent = nullptr);
    ~ClientLogin();
    void setupWindow();
    void staticGUIElements();
    QString getUserName();
    QString getPassword();
    QHostAddress getIPAddress();
    quint16 getPort();
    ///////////////////////////////////
    // The clientLogin attempts to login after providing all the details needed
    // as well as pressing the login button.
    ///////////////////////////////////
public slots:
    void attemptLogin();
    void loginStatus(bool loginSuccessful, QString reason);
    void connectionResult(int status, QString errorMsg);
    void serverDisconnected();
signals:
    //conect
    void connectToServer(QHostAddress serverIP, quint16 port, QString playerName, QString password);

    ///////////////////////////////////
    // The clientLogin attempts to login after providing all the details needed
    ///////////////////////////////////
private slots:
    //Client network slots.
    void on_infoButton_clicked();

private:
    Ui::ClientLogin *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    QString username;
    int pageID = 3;
    bool loginSuccessful;
};

#endif // CLIENTLOGIN_H
