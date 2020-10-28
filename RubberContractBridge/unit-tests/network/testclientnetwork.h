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
    QString passwordServer;
    quint16 port;
    QHostAddress ip;
    QString playerName;
    ServerNetwork testServerNet1;

    QSignalSpy *spyServer;
    QSignalSpy *spyServerPlayerJoined;
    QSignalSpy *spyServerError;
    QSignalSpy *spyServerPlayerDisconnected;

};

#endif // TESTCLIENTNETWORK_H
