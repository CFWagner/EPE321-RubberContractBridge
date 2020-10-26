#include "testplayernetwork.h"

// TODO: Test gameTerminated signal here.

testPlayerNetwork::testPlayerNetwork(QObject *parent) : QObject(parent)
{

    // Start a server and verify that it is working
    passwordServer = "abcdef1234$#^";
    port = 61076;
    ip = QHostAddress::LocalHost;
    testServerNetA.setPassword(passwordServer);

    // Monitor the connectionResult signal
    qRegisterMetaType<QHostAddress>();
    spyServer = new QSignalSpy(&testServerNetA, SIGNAL(connectionResult(int,QHostAddress,quint16,QString)));
    spyServerError = new QSignalSpy(&testServerNetA, SIGNAL(generalError(QString)));
    spyServerPlayerJoined = new QSignalSpy(&testServerNetA, SIGNAL(playerJoined(QString)));
    spyServerPlayerDisconnected = new QSignalSpy(&testServerNetA, SIGNAL(playerDisconnected(QString)));
}

/**
 * Destructor
 */

testPlayerNetwork::~testPlayerNetwork()
{
    // Ensure that all QSignalSpy objects are deleted.
    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();
    spyServerPlayerDisconnected->deleteLater();

    spyClientConnectResult1->deleteLater();
    spyClientError1->deleteLater();
    spyClientLoginResult1->deleteLater();
    spyClientServerDisconnected1->deleteLater();
    spyClientGameTerminated1->deleteLater();

    spyClientConnectResult2->deleteLater();
    spyClientError2->deleteLater();
    spyClientLoginResult2->deleteLater();
    spyClientServerDisconnected2->deleteLater();
    spyClientGameTerminated2->deleteLater();

    generalError1->deleteLater();
    clientDisconnected1->deleteLater();

    generalError2->deleteLater();
    clientDisconnected2->deleteLater();

    testPlayerNet1->deleteLater();
    testPlayerNet2->deleteLater();

    testServerNetA.deleteLater();
    testClientNet1.deleteLater();
    testClientNet2.deleteLater();
}

/**
 * Setup and verify the server.
 */

void testPlayerNetwork::verifyServerWorking()
{
    QVERIFY(spyServer->isValid());
    QVERIFY(spyServerError->isValid());
    QVERIFY(spyServerPlayerJoined->isValid());
    QVERIFY(spyServerPlayerDisconnected->isValid());

    // Server should be able to connect to port.
    testServerNetA.initServer(ip,port);



    QList<QVariant> arguments = spyServer->takeFirst();
    qInfo() << arguments;
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Were any generalError's emited from testServerNet1?
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");

}

/**
 * Add clients, verfiy the signals, log into server.
 */

void testPlayerNetwork::addClients()
{
    // Connect QSpySignal to all relevant signals from the class.
    spyClientConnectResult1 = new QSignalSpy(&testClientNet1,SIGNAL(connectionResult(int, QString)));
    spyClientError1 = new QSignalSpy(&testClientNet1,SIGNAL(generalError(QString)));
    spyClientLoginResult1 = new QSignalSpy(&testClientNet1,SIGNAL(loginResult(bool, QString)));
    spyClientServerDisconnected1 = new QSignalSpy(&testClientNet1,SIGNAL(serverDisconnected()));
    spyClientGameTerminated1 = new QSignalSpy(&testClientNet1,SIGNAL(gameTerminated(QString)));

    spyClientConnectResult2 = new QSignalSpy(&testClientNet2,SIGNAL(connectionResult(int, QString)));
    spyClientError2 = new QSignalSpy(&testClientNet2,SIGNAL(generalError(QString)));
    spyClientLoginResult2 = new QSignalSpy(&testClientNet2,SIGNAL(loginResult(bool, QString)));
    spyClientServerDisconnected2 = new QSignalSpy(&testClientNet2,SIGNAL(serverDisconnected()));
    spyClientGameTerminated2 = new QSignalSpy(&testClientNet2,SIGNAL(gameTerminated(QString)));

    // Verify signals
    QVERIFY(spyClientConnectResult1->isValid());
    QVERIFY(spyClientError1->isValid());
    QVERIFY(spyClientLoginResult1->isValid());
    QVERIFY(spyClientServerDisconnected1->isValid());
    QVERIFY(spyClientGameTerminated1->isValid());

    QVERIFY(spyClientConnectResult2->isValid());
    QVERIFY(spyClientError2->isValid());
    QVERIFY(spyClientLoginResult2->isValid());
    QVERIFY(spyClientServerDisconnected2->isValid());
    QVERIFY(spyClientGameTerminated2->isValid());

    // TODO: login to the server and get tcpsockets, so that players can be initialised.
    // Do first test on notification_bid.

}

/**
 * Get QTcpSocket, create the players. Test signals if you have time.
 */

void testPlayerNetwork::addPlayers()
{

}
