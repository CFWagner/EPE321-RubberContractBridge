#ifndef TESTSERVERLOGIN_H
#define TESTSERVERLOGIN_H

#include "game-server/server.h"
#include "gui/serverlogin.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>

#ifndef DECLARE_METATYPE_QHostAddress
#define DECLARE_METATYPE_QHostAddress
Q_DECLARE_METATYPE(QHostAddress);
#endif // DECLARE_METATYPE_QHostAddress

class testServerLogin : public QObject
{
    Q_OBJECT
public:
    explicit testServerLogin(QObject *parent = nullptr);
    ~testServerLogin();
private slots:
    void testSerLog();
signals:

private:
    ServerLogin *testSLog;
    Server *createServer;
    QSignalSpy *passwordSent;
    QSignalSpy *addressSent;
};

#endif // TESTSERVERLOGIN_H
