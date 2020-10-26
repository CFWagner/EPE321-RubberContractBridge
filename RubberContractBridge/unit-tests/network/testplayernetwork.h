#ifndef TESTPLAYERNETWORK_H
#define TESTPLAYERNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "network/servernetwork.h"
#include "network/clientnetwork.h"
#include "network/playernetwork.h"

class testPlayerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testPlayerNetwork(QObject *parent = nullptr);
    ~testPlayerNetwork();

private slots:
    // All private slots should be run in the following order, since they depend on each other.
    void verifyServerWorking();
    void addClients();
    void addPlayers();

signals:


private:
    QString passwordServer;
    quint16 port;
    QHostAddress ip;
    QString playerName;

    QString playerName1;
    QString playerName2;

    ServerNetwork testServerNetA;
    ClientNetwork testClientNet1;
    ClientNetwork testClientNet2;
    PlayerNetwork *testPlayerNet1;
    PlayerNetwork *testPlayerNet2;

    QSignalSpy *spyServer;
    QSignalSpy *spyServerPlayerJoined;
    QSignalSpy *spyServerError;
    QSignalSpy *spyServerPlayerDisconnected;

    QSignalSpy *spyClientConnectResult1;
    QSignalSpy *spyClientError1;
    QSignalSpy *spyClientLoginResult1;
    QSignalSpy *spyClientServerDisconnected1;
    QSignalSpy *spyClientGameTerminated1;

    QSignalSpy *spyClientConnectResult2;
    QSignalSpy *spyClientError2;
    QSignalSpy *spyClientLoginResult2;
    QSignalSpy *spyClientServerDisconnected2;
    QSignalSpy *spyClientGameTerminated2;

    QSignalSpy *generalError1;
    QSignalSpy *clientDisconnected1;

    QSignalSpy *generalError2;
    QSignalSpy *clientDisconnected2;
};

#endif // TESTPLAYERNETWORK_H
