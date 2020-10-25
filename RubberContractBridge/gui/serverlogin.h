#ifndef SERVERLOGIN_H
#define SERVERLOGIN_H

#include "hover.h"
#include "serverlobby.h"
#include "game-server/server.h"
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

public slots:
    // The server attempts to create the server given the details provided.
    void tryConnect();
signals:
    void sendServerPassword (QString password);
    void sendIPAddressPort (QHostAddress ipAddress,quint16 portID);

private:
    Ui::ServerLogin *ui;
    int pageID = 1;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    quint16 defaultPort = 61074;

    Server *serverCreated;


};

#endif // SERVERLOGIN_H
