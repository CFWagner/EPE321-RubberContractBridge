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

public slots:
    // The server attempts to create the server given the details provided.
    void tryConnect();
private:
    Ui::ServerLogin *ui;
    int pageID = 1;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    quint16 defaultPort = 61074;


};

#endif // SERVERLOGIN_H
