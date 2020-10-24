#include "testclientnetwork.h"

testClientNetwork::testClientNetwork(QObject *parent) : QObject(parent)
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
}

testClientNetwork::~testClientNetwork()
{
    // Ensure that all QSignalSpy objects are deleted.
    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();
}

void testClientNetwork::verifyServerWorking()
{
    QVERIFY(spyServer->isValid());
    QVERIFY(spyServerError->isValid());
    QVERIFY(spyServerPlayerJoined->isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spyServer->takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Were any generalError's emited from testServerNet1?
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");

    // Test the generalError signal
    testServerNet1.getUnitTest();
    QVERIFY2(spyServerError->count() == 1,"General errors occured in the testServerNet1.");
    QList<QVariant> arguments2 = spyServerError->takeFirst();
    QCOMPARE(arguments2.at(0), "bUnitTest was requested, but it isn't being used anymore.");
}

/*!
 * \brief Test the connection, data sent over in QJsonObject format and login.
 */

void testClientNetwork::LoginCorrectly()
{
    // Start a clientNetwork (this should work)
    playerName = "TestPlayer 1";
    // When transaction is done, this will execute.
    ClientNetwork testClient1;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient1,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient1,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient1,SIGNAL(loginResult(bool, QString)));


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,port,playerName,passwordServer);
    QVERIFY(spyClientLoginResult.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);
    QList<QVariant> arguments = spyServerPlayerJoined->takeFirst();
    QCOMPARE(arguments.at(0), playerName);

}

/*!
 * \brief Test wrong password and username. Test when multiple clients connect to server.
 */

void testClientNetwork::wrongServerDetails()
{
    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();

    // Start a clientNetwork (this should work)
    playerName = "TestPlayer 1";

    // Use wrong password.
    QString password_wrong = "hiodaf jdf";
    // When transaction is done, this will execute.

    ClientNetwork testClient;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient,SIGNAL(loginResult(bool, QString)));

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient.txRequestLogin(ip,port,playerName,password_wrong);

    QVERIFY(spyClientLoginResult.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult.count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The password is incorrect.");

    QVERIFY(spyServerPlayerJoined->count() == 0);


    // Login with correct password after loggin in with wrong password.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient.txRequestLogin(ip,port,playerName,passwordServer);

    QVERIFY(spyClientLoginResult.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult.count(), 1);

    argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);

    // Try to connect again after already being connected


    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.

    qInfo() << "Before trying to reconnect to server while being connected.";

    testClient.txRequestLogin(ip,port,playerName,passwordServer);

//    QVERIFY(spyClientConnectResult.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult.count(), 0);
    QCOMPARE(spyClientConnectResult.count(), 1);

    argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be unsucsessfull.
    QCOMPARE(argumentsC.at(0), 3);

    QVERIFY(spyServerPlayerJoined->count() == 0);

    // ------ Let a second player join with same name -------
    // The connection should work, but the server should send and error and disconnect the client.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();

    // Start a clientNetwork
    QString playerName2 = "TestPlayer 2";

    ClientNetwork testClient2;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult2(&testClient2,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError2(&testClient2,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult2(&testClient2,SIGNAL(loginResult(bool, QString)));

    // Do something that can result in problems.
    // (Log into the server.)
    testClient2.txRequestLogin(ip,port,playerName,passwordServer);

    QVERIFY(spyClientLoginResult2.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError2.count() == 0,"General errors occured in the testClient2.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The palyer's name has already been used, please choose another username.");

    QVERIFY(spyServerPlayerJoined->count() == 0);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();


    // ---- Use the name of the AI -------
    // Do something that can result in problems.
    // (Log into the server.)
    testClient2.txRequestLogin(ip,port,"AI",passwordServer);

    QVERIFY(spyClientLoginResult2.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError2.count() == 0,"General errors occured in the testClient2.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    // Proof that QJsonObject data transfer works.
    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The palyer may not be given the same name as an AI. AI's name is: AI");

    QVERIFY(spyServerPlayerJoined->count() == 0);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();



    // ---- Use a name longer than 15 chars -------
    // Do something that can result in problems.
    // (Log into the server.)
    testClient2.txRequestLogin(ip,port,"1234567890123456",passwordServer);

    QVERIFY(spyClientLoginResult2.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError2.count() == 0,"General errors occured in the testClient2.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The player name may not be longer than 15 chars.");

    QVERIFY(spyServerPlayerJoined->count() == 0);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();


    // ------ Sucessfully connect a second player ---------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient2.txRequestLogin(ip,port,playerName2,passwordServer);

    QVERIFY(spyClientLoginResult2.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError2.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);


}

/*!
 * \brief Test when client is configured with incorrect ip and/or port.
 */

void testClientNetwork::incorrectSocket()
{
    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();


    // Start a clientNetwork (this should work)
    playerName = "Random player";
    // When transaction is done, this will execute.
    ClientNetwork testClient1;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient1,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient1,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient1,SIGNAL(loginResult(bool, QString)));

    // Try to connect with wrong IP
    QHostAddress IP_wrong = QHostAddress("192.168.56.1");
    quint16 portWrong = 61070;


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(IP_wrong,portWrong,playerName,passwordServer);
    QVERIFY(spyClientConnectResult.wait(30000));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 0);
    QCOMPARE(spyClientConnectResult.count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 1);
    QCOMPARE(argumentsC.at(1),"The connection was refused by the server. Make sure the server is running, "
                              "and check that the host IP address and port settings are correct.");

    QVERIFY(spyServerPlayerJoined->count() == 0);


    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();

    // ------- Wrong ip only -------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(IP_wrong,port,playerName,passwordServer);
    QVERIFY(spyClientConnectResult.wait(30000));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 0);
    QCOMPARE(spyClientConnectResult.count(), 1);

    argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 1);
    QCOMPARE(argumentsC.at(1),"The connection was refused by the server. Make sure the server is running, "
                              "and check that the host IP address and port settings are correct.");

    QVERIFY(spyServerPlayerJoined->count() == 0);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();

    // ------- Wrong port only -------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,portWrong,playerName,passwordServer);
    QVERIFY(spyClientConnectResult.wait(20000));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 0);
    QCOMPARE(spyClientConnectResult.count(), 1);

    argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 1);
    QCOMPARE(argumentsC.at(1),"The connection was refused by the server. Make sure the server is running, "
                              "and check that the host IP address and port settings are correct.");

    QVERIFY(spyServerPlayerJoined->count() == 0);
}


/**
 * Test the getPlayerSoc function as well as the stopListening function.
 */

void testClientNetwork::getPlayers()
{
    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();


    // Start a clientNetwork (this should work)
    playerName = "Player 10"; // Do not change this name, since it is used in following tests.
    // When transaction is done, this will execute.
    ClientNetwork testClient1;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient1,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient1,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient1,SIGNAL(loginResult(bool, QString)));

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,port,playerName,passwordServer);
    QVERIFY(spyClientLoginResult.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");

    QCOMPARE(spyClientLoginResult.count(), 1);

    QList<QVariant> argumentsC = spyClientConnectResult.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);
    QList<QVariant> arguments = spyServerPlayerJoined->takeFirst();
    QCOMPARE(arguments.at(0), playerName);

    // ------ Let a second player join with same name -------
    // The connection should work, but the server should send and error and disconnect the client.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();

    // Start a clientNetwork
    QString playerName2 = "Player 20"; // Do not change this name, since it is used in following tests.

    ClientNetwork testClient2;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult2(&testClient2,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError2(&testClient2,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult2(&testClient2,SIGNAL(loginResult(bool, QString)));

    // ------ Sucessfully connect a second player ---------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient2.txRequestLogin(ip,port,playerName2,passwordServer);

    QVERIFY(spyClientLoginResult2.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError2.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();

    // Stop listening
    testServerNet1.stopListening();

    // Try to connect another client
    // Start a clientNetwork
    QString playerName3 = "Player 30"; // Do not change this name, since it is used in following tests.

    ClientNetwork testClient3;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult3(&testClient3,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError3(&testClient3,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult3(&testClient3,SIGNAL(loginResult(bool, QString)));

    // ------ Third player should no be able to connect ---------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient3.txRequestLogin(ip,port,playerName3,passwordServer);

    QVERIFY(spyClientLoginResult3.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError3.count() == 0,"General errors occured in the testClient.");

    QCOMPARE(spyClientLoginResult3.count(), 1);

    argumentsC = spyClientConnectResult3.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult3.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The game is in progress and no more players are allowed on this server.");

    QVERIFY(spyServerPlayerJoined->count() == 0);

    // Tests getPlayerSockets

    // Try to get an invalid player name.
    // nullptr should be returned
    QTcpSocket* getPlayerSocket1 = testServerNet1.getPlayerSoc(playerName3);
    QVERIFY2(getPlayerSocket1 == nullptr,"Wrong player name requested, thus nullptr should have been returned.");

    // Use the correct player name.
    // The second client's soceket should be returned.
    QTcpSocket* getPlayerSocket2 = testServerNet1.getPlayerSoc(playerName2);
    QVERIFY2(getPlayerSocket2 != nullptr,"Correct player name requested, thus nullptr should not have been returned.");

    // Try to get an player that has already been removed.
    // nullptr should be returned
    QVERIFY2(testServerNet1.getPlayerSoc(playerName2) == nullptr,"Wrong player name requested, thus nullptr should have been returned.");

    // Use the other correct player name.
    // The first client's soceket should be returned.
    getPlayerSocket1 = testServerNet1.getPlayerSoc(playerName);
    QVERIFY2(getPlayerSocket1 != nullptr,"Correct player name requested, thus nullptr should not have been returned.");

    // Test to see if it is the correct player.
    // Disconnect the one player 2.
    // TODO: start a game and then disconnect the client (from the server side).
    // Then test if the correct client emits gameTerminated.
    // Repeat for the other client.


}

void testClientNetwork::cleanupTestCase()
{
    // Ensure that all QSignalSpy objects are deleted.
    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();
    qInfo() << "Deleted the spyServerError";
}



void testClientNetwork::testFunc()
{

}
