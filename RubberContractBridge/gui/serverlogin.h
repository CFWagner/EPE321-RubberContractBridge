#ifndef SERVERLOGIN_H
#define SERVERLOGIN_H

#include "hover.h"
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
    void tryConnect();
    void connectionResult(int status, QHostAddress ip, quint16 port, QString errorMsg);
    void generalError(QString errorMsg);
    //    QString getPassword();
    //    QHostAddress getIPAddress();
    //    quint16 getPort();

signals:
    void serverPassword (QString password);
    void serverIPAddressPort(QHostAddress addressSent,quint16 portSent);
    void createLobby();

private:
    Ui::ServerLogin *ui;
    int pageID = 1;
    QString password ="";
    quint16 portID = 61074;
    QHostAddress ipAddress = QHostAddress::LocalHost;

};

#endif // SERVERLOGIN_H
