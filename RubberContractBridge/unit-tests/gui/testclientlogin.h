#ifndef TESTCLIENTLOGIN_H
#define TESTCLIENTLOGIN_H

#include "gui/clientlogin.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>

#ifndef DECLARE_METATYPE_QHostAddress
#define DECLARE_METATYPE_QHostAddress
Q_DECLARE_METATYPE(QHostAddress);
#endif // DECLARE_METATYPE_QHostAddress

class testClientLogin : public QObject
{
    Q_OBJECT
public:
    explicit testClientLogin(QObject *parent = nullptr);
    ~testClientLogin();
private slots:
    void testClientLog();
signals:
    void connectionResult(int status, QString errorMsg);
private:
    ClientLogin *testCL;
    QSignalSpy *connectClient;
    QSignalSpy *connectResult;
};

#endif // TESTCLIENTLOGIN_H
