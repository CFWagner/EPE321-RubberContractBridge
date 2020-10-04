#ifndef TESTCLIENTNETWORK_H
#define TESTCLIENTNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "network/servernetwork.h"
#include "network/clientnetwork.h"

class testClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testClientNetwork(QObject *parent = nullptr);
    ~testClientNetwork();


private slots:
    void Login();


signals:

private:


    QString passwordServer;
    quint16 port;
    QHostAddress ip;
    QString playerName;
    ServerNetwork testServerNet1;
    ClientNetwork testClient1;

    QSignalSpy *spyServer;
    QSignalSpy *spyServerPlayerJoined;
    QSignalSpy *spyServerError;

    QSignalSpy *spyClientConnectResult;
    QSignalSpy *spyClientLoginResult;
    QSignalSpy *spyClientError;

};

#endif // TESTCLIENTNETWORK_H
