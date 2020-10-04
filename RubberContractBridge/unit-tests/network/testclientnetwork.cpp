#include "testclientnetwork.h"

testClientNetwork::testClientNetwork(QObject *parent) : QObject(parent)
{

}

void testClientNetwork::Login()
{
    // Start a server and verify that it is working
    QString passwordServer = "abcdef1234$#@";
    quint16 port = 61074;
    QHostAddress ip = QHostAddress::LocalHost;
    ServerNetwork testServerNet1;
    testServerNet1.setPassword(passwordServer);

    // Monitor the connectionResult signal
    qRegisterMetaType<QHostAddress>();
    QSignalSpy spyServer(&testServerNet1, SIGNAL(connectionResult(int,QHostAddress,quint16,QString)));
    QSignalSpy spyServerError(&testServerNet1, SIGNAL(generalError(QString)));
    QSignalSpy spyServerPlayerJoined(&testServerNet1, SIGNAL(playerJoined(QString)));

    QVERIFY(spyServer.isValid());
    QVERIFY(spyServerError.isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spyServer.takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Were any generalError's emited from testServerNet1?
    QVERIFY2(spyServerError.count() == 0,"General errors occured in the testServerNet1.");


    // Start a clientNetwork (this should work)
    QString playerName = "TestPlayer 1";
    ClientNetwork testClient1;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient1,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient1,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient1,SIGNAL(loginResult(bool, QString)));


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,port,playerName,passwordServer);

    QVERIFY(spyClientLoginResult.wait(1000));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError.count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined.count() == 1);
    arguments = spyServerPlayerJoined.takeFirst();
    QCOMPARE(arguments.at(0), playerName);




}
