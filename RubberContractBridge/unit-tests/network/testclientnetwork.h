#ifndef TESTCLIENTNETWORK_H
#define TESTCLIENTNETWORK_H

// TODO: Unit test serverDisconnected signal. (Once game has started.)
// TODO: Set gameStarted = true once game has started.

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
    // All private slots should be run in the following order, since they depend on each other.
    void verifyServerWorking();
    void LoginCorrectly();
    void wrongServerDetails();
    void incorrectSocket();
    void getPlayers();
    void cleanupTestCase();

signals:

private:
    void testFunc();


    QString passwordServer;
    quint16 port;
    QHostAddress ip;
    QString playerName;
    ServerNetwork testServerNet1;

    QSignalSpy *spyServer;
    QSignalSpy *spyServerPlayerJoined;
    QSignalSpy *spyServerError;

};

#endif // TESTCLIENTNETWORK_H
