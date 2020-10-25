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

public slots:
    // The clientLogin attempts to login after providing all the details needed
    // as well as pressing the login button.
    void attemptLogin();

private slots:
    void on_infoButton_clicked();

private:
    Ui::ClientLogin *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    QString username;
    int pageID = 3;
};

#endif // CLIENTLOGIN_H
