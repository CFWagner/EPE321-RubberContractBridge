#ifndef SERVERLOGIN_H
#define SERVERLOGIN_H

#include "hover.h"
#include "serverlobby.h"
#include <QHostAddress>
#include <QWidget>
#include <QObject>
#include <QDebug>

namespace Ui {
class ServerLogin;
}

class ServerLogin : public QWidget
{
    Q_OBJECT

public:
    explicit ServerLogin(QWidget *parent = nullptr);
    ~ServerLogin();
    void setupWindow();
    void staticGUIElements();
    bool checkValidPassword();
    ServerLobby *serverLob;

public slots:
    // The server attempts to create the server given the details provided.
    void tryConnect();
    // Display any errors when sending the password and IPAddress
    void connectionResult(int status, QHostAddress ip, quint16 port, QString errorMsg);
    void generalError(QString errorMsg);
    QString getPassword();
    QHostAddress getIPAddress();
    quint16 getPort();
signals:
    // Send the password and IPAddress to the server.
    void serverPassword (QString password);
    void serverIPAddressPort (QHostAddress ipAddress,quint16 portID);

private:
    Ui::ServerLogin *ui;
    int pageID = 1;
    QString password;
    quint16 portID = 61074;
    QHostAddress ipAddress = QHostAddress::LocalHost;
};

#endif // SERVERLOGIN_H
