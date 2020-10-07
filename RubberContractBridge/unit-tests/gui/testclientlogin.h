#ifndef TESTCLIENTLOGIN_H
#define TESTCLIENTLOGIN_H
#include "gui/entrywindow.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>


class testclientlogin : public QObject
{
    Q_OBJECT
public:
    explicit testclientlogin(QObject *parent = nullptr);
    ~testclientlogin();
signals:

private slots:
    void Login();
private:
    clientLogin testLogin;
    QSignalSpy *spyLogin;
    QString passwordServer;
    quint16 port;
    QHostAddress ipAddress;
    QString username;
};

#endif // TESTCLIENTLOGIN_H
