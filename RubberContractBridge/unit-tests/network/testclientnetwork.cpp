#include "testclientnetwork.h"

testClientNetwork::testClientNetwork(QObject *parent) : QObject(parent)
{

}

testClientNetwork::~testClientNetwork()
{
    // Ensure that all QSignalSpy objects are deleted.
    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();

    spyClientConnectResult->deleteLater();
    spyClientLoginResult->deleteLater();
    spyClientError->deleteLater();
}


void testClientNetwork::Login()
{
    // Start a server and verify that it is working
    passwordServer = "abcdef1234$#@";
    port = 61074;
    ip = QHostAddress::LocalHost;
    testServerNet1.setPassword(passwordServer);

    // Monitor the connectionResult signal
    qRegisterMetaType<QHostAddress>();
    spyServer = new QSignalSpy(&testServerNet1, SIGNAL(connectionResult(int,QHostAddress,quint16,QString)));
    spyServerError = new QSignalSpy(&testServerNet1, SIGNAL(generalError(QString)));
    spyServerPlayerJoined = new QSignalSpy(&testServerNet1, SIGNAL(playerJoined(QString)));

    QVERIFY(spyServer->isValid());
    QVERIFY(spyServerError->isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spyServer->takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Were any generalError's emited from testServerNet1?
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");


    // Start a clientNetwork (this should work)
    playerName = "TestPlayer 1";
    // When transaction is done, this will execute.
//    connect(&testClient1,&ClientNetwork::loginResult,this,&testClientNetwork::LoginCont);

    // Connect QSpySignal to all relevant signals from the class.
    spyClientConnectResult = new  QSignalSpy(&testClient1,SIGNAL(connectionResult(int, QString)));
    spyClientError = new QSignalSpy(&testClient1,SIGNAL(generalError(QString)));
    spyClientLoginResult = new QSignalSpy (&testClient1,SIGNAL(loginResult(bool, QString)));


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,port,playerName,passwordServer);
    qInfo() << "Just before wait.";
    QVERIFY(spyClientLoginResult->wait(5000));
    qInfo() << "Just after wait.";

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError->count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult->count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult->takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult->takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);
    arguments = spyServerPlayerJoined->takeFirst();
    QCOMPARE(arguments.at(0), playerName);



}
