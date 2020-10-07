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
    void windowSetup();
    void attemptLogin();

private slots:
    void on_loginButton_clicked();
    void on_infoButton_clicked();
signals:
    void connectToServer(QHostAddress ipAddress,quint16 portID, QString username, QString password);
private:
    Ui::clientLogin *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    QString username;
};

#endif // CLIENTLOGIN_H
