#ifndef TESTSERVERLOGIN_H
#define TESTSERVERLOGIN_H
#include "gui/entrywindow.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>

class TestServerLogin : public QObject
{
    Q_OBJECT
public:
    explicit TestServerLogin(QObject *parent = nullptr);
    ~TestServerLogin();
signals:

private slots:
    void Login();
private:
    ServerGUI testservergui;
    QSignalSpy *spyPassword;
    QSignalSpy *spyAddress;
    QString passwordServer;
    quint16 port;
    QHostAddress ipAddress;
};

#endif // TESTSERVERLOGIN_H
