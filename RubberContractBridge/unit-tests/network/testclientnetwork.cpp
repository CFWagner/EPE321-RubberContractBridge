#include "testclientnetwork.h"

/**
 * Constructor
 * @param parent
 */

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
    spyServerPlayerDisconnected = new QSignalSpy(&testServerNet1, SIGNAL(playerDisconnected(QString)));
}

/**
 * Startup the server that will be used for all the tests
 * and validate that the server is working.
 */

void testClientNetwork::verifyServerWorking()
{
    QVERIFY(spyServer->isValid());
    QVERIFY(spyServerError->isValid());
    QVERIFY(spyServerPlayerJoined->isValid());
    QVERIFY(spyServerPlayerDisconnected->isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spyServer->takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Were any generalError's emited from testServerNet1?
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

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
    // Wait for previous slot to finish executing. (Deleteing all vaiables.)
    spyServerPlayerDisconnected->wait(100);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();

    // Start a clientNetwork (this should work)
    playerName = "TestPlayer 100";

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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");


    // Login with correct password after loggin in with wrong password.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");


    // Try to connect again after already being connected

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();


    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.

    qInfo() << "Before trying to reconnect to server while being connected.";

    testClient.txRequestLogin(ip,port,playerName,passwordServer);

    // QVERIFY(spyClientConnectResult.wait(100));

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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    // ------ Let a second player join with same name -------
    // The connection should work, but the server should send and error and disconnect the client.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QCOMPARE(argumentsC.at(1), "The player's name has already been used, please choose another username.");

    QVERIFY(spyServerPlayerJoined->count() == 0);
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QCOMPARE(argumentsC.at(1), "The player's name may not contain \"AI\".");

    QVERIFY(spyServerPlayerJoined->count() == 0);
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");


    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();

    // Add up to 11 players. (Max is 10 players.)

    QVector<ClientNetwork*> arrTestClientNet;
    QVector<QString> arrPlayerNames;

    // Add another 7 players (for a total of 9)
    for (int i = 0; i < 8; i++){
        arrTestClientNet.append(new ClientNetwork());
        arrPlayerNames.append("Test player " + QString::number(i+3));
        qInfo() << "Added: " << arrPlayerNames.at(i);
        arrTestClientNet.at(i)->txRequestLogin(ip,port,arrPlayerNames.at(i),passwordServer);
        QVERIFY(spyServerPlayerJoined->wait(100));
        QVERIFY(spyServerPlayerJoined->count() == i+1);
    }

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();

    // Try to connect the 11 player
    // Start a clientNetwork
    QString playerName11 = "TestPlayer 11";

    ClientNetwork testClient11;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult11(&testClient11,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError11(&testClient11,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult11(&testClient11,SIGNAL(loginResult(bool, QString)));

    // Do something that can result in problems.
    // (Log into the server.)
    testClient11.txRequestLogin(ip,port,playerName11,passwordServer);

    QVERIFY(spyClientLoginResult11.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError11.count() == 0,"General errors occured in the testClient11.");

    QCOMPARE(spyClientLoginResult11.count(), 1);

    argumentsC = spyClientConnectResult11.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult11.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The lobby is full. A maximum of 10 players may be added to the lobby.");

    QVERIFY(spyServerPlayerJoined->count() == 0); // The player should not have been allowed to join.
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError11.clear();
    spyClientLoginResult11.clear();
    spyClientConnectResult11.clear();

    // Delete all ClietnNetowrk Objects
    for (int i = 0; i < 8; i++){
        arrTestClientNet.at(i)->deleteLater();
    }
}

/*!
 * \brief Test when client is configured with incorrect ip and/or port.
 */

void testClientNetwork::incorrectSocket()
{
    // Wait for previous function to finish executing.
    // One wait for each client that needs to disconnect.
    for (int i = 0; i < 10; i++){
           spyServerPlayerDisconnected->wait(100);
       }

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();


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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");


    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
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
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");
}


/**
 * Test the getPlayerSoc function as well as the stopListening function.
 */

void testClientNetwork::getPlayers()
{
    // Wait for previous slot to finish executing. (Deleteing all vaiables.)
    spyServerPlayerDisconnected->wait(100);

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();


    // Start a clientNetwork (this should work)
    playerName = "Player 10"; // Do not change this name, since it is used in following tests.
    // When transaction is done, this will execute.
    ClientNetwork testClient1;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult(&testClient1,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError(&testClient1,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult(&testClient1,SIGNAL(loginResult(bool, QString)));
    QSignalSpy spyClientServerDisconnected1(&testClient1,SIGNAL(serverDisconnected()));

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient1.txRequestLogin(ip,port,playerName,passwordServer);
    QVERIFY(spyClientLoginResult.wait(100));

    // No warnings should be issused by either the server or the client
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet1.");
    QVERIFY2(spyClientError.count() == 0,"General errors occured in the testClient1.");
    QVERIFY2(spyClientServerDisconnected1.count() == 0,"Server unexpectedly disconnected.");

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

    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    // ------ Let a second player join with same name -------
    // The connection should work, but the server should send and error and disconnect the client.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientServerDisconnected1.clear();

    // Start a clientNetwork
    QString playerName2 = "Player 20"; // Do not change this name, since it is used in following tests.

    ClientNetwork testClient2;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult2(&testClient2,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError2(&testClient2,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult2(&testClient2,SIGNAL(loginResult(bool, QString)));
    QSignalSpy spyClientServerDisconnected2(&testClient2,SIGNAL(serverDisconnected()));

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
    QVERIFY2(spyClientServerDisconnected2.count() == 0,"Server unexpectedly disconnected.");

    QCOMPARE(spyClientLoginResult2.count(), 1);

    argumentsC = spyClientConnectResult2.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult2.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientServerDisconnected1.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();
    spyClientServerDisconnected2.clear();


    // ------ Let a 4th player join with same name -------
    // This player is added to test how the server responds to an unexpended disconnection of the clients.
    // The 3rd player will be tried to be added after the 4th player.
    // The connection should work, but the server should send and error and disconnect the client.

    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientServerDisconnected1.clear();

    // Start a clientNetwork
    QString playerName4 = "Player 40"; // Do not change this name, since it is used in following tests.

    ClientNetwork testClient4;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult4(&testClient4,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError4(&testClient4,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult4(&testClient4,SIGNAL(loginResult(bool, QString)));
    QSignalSpy spyClientServerDisconnected4(&testClient4,SIGNAL(serverDisconnected()));

    // ------ Sucessfully connect a 4th player ---------

    // Do something that can result in problems.
    // (Log into the server.)
    // Remember to monitor both the client and the server.
    testClient4.txRequestLogin(ip,port,playerName4,passwordServer);

    QVERIFY(spyClientLoginResult4.wait(100));

    // No warnings should be issused by either the server or the client
    // Proof that data sent in QJsonObject format is working.
    QVERIFY2(spyServerError->count() == 0,"General errors occured in the testServerNet.");
    QVERIFY2(spyClientError4.count() == 0,"General errors occured in the testClient.");
    QVERIFY2(spyClientServerDisconnected4.count() == 0,"Server unexpectedly disconnected.");

    QCOMPARE(spyClientLoginResult4.count(), 1);

    argumentsC = spyClientConnectResult4.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult4.takeFirst();
    QCOMPARE(argumentsC.at(0), true);
    QCOMPARE(argumentsC.at(1), "");

    QVERIFY(spyServerPlayerJoined->count() == 1);
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");


    // Forecfully disconnect the client from the server.
    // Server should emit playerDisconnected signal when player is in the lobby.
    // testClient4 is in the lobby.
    testClient4.abort();
    QVERIFY(spyServerPlayerDisconnected->wait(100));

    QVERIFY2(spyServerPlayerDisconnected->count() == 1,"Player should have disconnected from testServerNet1.");
    QCOMPARE(spyServerError->count(), 0); // No generalError given when client unexpectedly disconnects.


    spyServerPlayerJoined->clear();
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerDisconnected->clear();
    spyClientError.clear();
    spyClientLoginResult.clear();
    spyClientConnectResult.clear();
    spyClientServerDisconnected1.clear();
    spyClientError2.clear();
    spyClientLoginResult2.clear();
    spyClientConnectResult2.clear();
    spyClientServerDisconnected2.clear();
    spyClientError4.clear();
    spyClientLoginResult4.clear();
    spyClientConnectResult4.clear();
    spyClientServerDisconnected4.clear();

    // Tests getPlayerSockets
    QString playerName3 = "Player 30"; // Do not change this name, since it is used in following tests.

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

    qInfo() << "Before abort called in test.";
    qInfo() << "getPlayerSocket2: " << getPlayerSocket2 << " testClient1: " << &testClient1;
    getPlayerSocket2->abort();

    qInfo() << "After abort called in test.";
    QVERIFY(spyClientServerDisconnected2.wait(100));
    QVERIFY2(spyClientServerDisconnected2.count() == 1,"Server unexpectedly disconnected.");
    QVERIFY2(spyClientServerDisconnected1.count() == 0,"Server did not unexpectedly disconnected.");

    // Close the server
    getPlayerSocket1->abort();
    QVERIFY(spyClientServerDisconnected1.wait(100));
    QVERIFY2(spyClientServerDisconnected1.count() == 1,"Server unexpectedly disconnected.");

    // Stop listening
    testServerNet1.stopListening();

    // Try to connect another client
    // Start a clientNetwork
    ClientNetwork testClient3;

    // Connect QSpySignal to all relevant signals from the class.
    QSignalSpy spyClientConnectResult3(&testClient3,SIGNAL(connectionResult(int, QString)));
    QSignalSpy spyClientError3(&testClient3,SIGNAL(generalError(QString)));
    QSignalSpy spyClientLoginResult3(&testClient3,SIGNAL(loginResult(bool, QString)));
    QSignalSpy spyClientServerDisconnected3(&testClient3,SIGNAL(serverDisconnected()));

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
    QVERIFY2(spyClientServerDisconnected3.count() == 0,"Server unexpectedly disconnected.");

    QCOMPARE(spyClientLoginResult3.count(), 1);

    argumentsC = spyClientConnectResult3.takeFirst();
    // The connection should be sucsessfull.
    QCOMPARE(argumentsC.at(0), 0);

    argumentsC = spyClientLoginResult3.takeFirst();
    QCOMPARE(argumentsC.at(0), false);
    QCOMPARE(argumentsC.at(1), "The game is in progress and no more players are allowed on this server.");

    QVERIFY(spyServerPlayerJoined->count() == 0);
    QVERIFY2(spyServerPlayerDisconnected->count() == 0,"Player should not have disconnected from testServerNet1.");
}

void testClientNetwork::cleanupTestCase()
{
    // Ensure that all QSignalSpy objects are deleted.
    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();
    spyServerPlayerDisconnected->deleteLater();
    // testServerNet1.deleteLater();  // Gives a memory leak if executed.

    qInfo() << "testClientNetwork cleaded up";
}
