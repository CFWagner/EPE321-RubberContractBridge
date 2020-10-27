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

    for (int i = 0; i < testClientNet.count(); i++){
        qInfo() << i;
        spyClientConnectResult[i]->deleteLater();
        spyClientError[i]->deleteLater();
        spyClientLoginResult[i]->deleteLater();
        spyClientServerDisconnected[i]->deleteLater();
        spyClientGameTerminated[i]->deleteLater();

        spyClientNotifyBidTurn[i]->deleteLater();
        spyClientNotifyMoveTurn[i]->deleteLater();
        spyClientNotifyBidRejected[i]->deleteLater();
        spyClientNotifyMoveRejected[i]->deleteLater();
        spyClientUpdateGameState[i]->deleteLater();
        spyClientMessageReceived[i]->deleteLater();

        testClientNet[i]->deleteLater();
    }

    for (int i = 0; i < testPlayerNet.count(); i++){
        qInfo() << i;
        spyPlayerGeneralError[i]->deleteLater();
        spyPlayerBidSelected[i]->deleteLater();
        spyPlayerMoveSelected[i]->deleteLater();
        spyPlayerMessageGenerated[i]->deleteLater();
        spyPlayerClientDisconnected[i]->deleteLater();

        testPlayerNet[i]->deleteLater();
    }

    testServerNetA.deleteLater();
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
    QVERIFY(spyServerError->count() == 0);
}

/**
 * Add clients, verfiy the signals, log into server.
 */

void testPlayerNetwork::addClients()
{
    // Add
    addManyClients(4);
    addManyClients(2);

    // TODO: login to the server and get tcpsockets, so that players can be initialised.
    // Do first test on notification_bid.
    addPlayerNetwork(playerNames[2]);
    addPlayerNetwork(playerNames[3]);
    addPlayerNetwork(playerNames[1]);
    addPlayerNetwork(playerNames[0]);

    // The server should stop listening for new logon attempts
    testServerNetA.stopListening();

    // Calling the following function should make the test fail
    // addManyClients(1);

}

/**
 * Get QTcpSocket, create the players. Test signals if you have time.
 */

void testPlayerNetwork::addPlayers()
{

}

/**
 * Add the number of clients specified and log them into the server.
 * @param numberOfClients to be added to the server.
 */

void testPlayerNetwork::addManyClients(int numberOfClients)
{
    // Clear all server signals
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerJoined->clear();
    spyServerPlayerDisconnected->clear();

    // Set start and stop values
    int startNumClients = testClientNet.count();
    int upperLimit = numberOfClients + startNumClients;
    for (int i = startNumClients; i < upperLimit; i++){
        // Start a clientNetwork (this should work)
        playerNames.append("AutoPlayer " + QString::number(i));
        // When transaction is done, this will execute.
        testClientNet.append(new ClientNetwork);

        // Connect QSpySignal to all relevant signals from the class.
        spyClientConnectResult.append(new QSignalSpy(testClientNet[i], SIGNAL(connectionResult(int, QString))));
        spyClientError.append(new QSignalSpy(testClientNet[i], SIGNAL(generalError(QString))));
        spyClientLoginResult.append(new QSignalSpy(testClientNet[i], SIGNAL(loginResult(bool, QString))));
        spyClientServerDisconnected.append(new QSignalSpy(testClientNet[i], SIGNAL(serverDisconnected())));
        spyClientGameTerminated.append(new QSignalSpy(testClientNet[i], SIGNAL(gameTerminated(QString))));

        spyClientNotifyBidTurn.append(new QSignalSpy(testClientNet[i], SIGNAL(notifyBidTurn())));
        spyClientNotifyMoveTurn.append(new QSignalSpy(testClientNet[i], SIGNAL(notifyMoveTurn())));
        spyClientNotifyBidRejected.append(new QSignalSpy(testClientNet[i], SIGNAL(notifyBidRejected(QString))));
        spyClientNotifyMoveRejected.append(new QSignalSpy(testClientNet[i], SIGNAL(notifyMoveRejected(QString))));
        spyClientUpdateGameState.append(new QSignalSpy(testClientNet[i], SIGNAL(updateGameState(PlayerGameState))));
        spyClientMessageReceived.append(new QSignalSpy(testClientNet[i], SIGNAL(messageReceived(QString, QString))));

        // Verify signals
        QVERIFY(spyClientConnectResult[i]->isValid());
        QVERIFY(spyClientError[i]->isValid());
        QVERIFY(spyClientLoginResult[i]->isValid());
        QVERIFY(spyClientServerDisconnected[i]->isValid());
        QVERIFY(spyClientGameTerminated[i]->isValid());

        QVERIFY(spyClientNotifyBidTurn[i]->isValid());
        QVERIFY(spyClientNotifyMoveTurn[i]->isValid());
        QVERIFY(spyClientNotifyBidRejected[i]->isValid());
        QVERIFY(spyClientNotifyMoveRejected[i]->isValid());
        QVERIFY(spyClientUpdateGameState[i]->isValid());
        QVERIFY(spyClientMessageReceived[i]->isValid());

        // Remember to monitor both the client and the server.
        testClientNet[i]->txRequestLogin(ip,port,playerNames[i],passwordServer);
        QVERIFY(spyClientLoginResult[i]->wait(100));

        // No warnings should be issused by either the server or the client
        QVERIFY(spyServerError->count() == 0);
        QVERIFY(spyClientError[i]->count() == 0);
        QVERIFY(spyServerPlayerDisconnected->count() == 0);
        QCOMPARE(spyClientLoginResult[i]->count(), 1);
        qInfo() << "The value of i: " << i << *spyServerPlayerJoined;
        QCOMPARE(spyServerPlayerJoined->count(), i-startNumClients+1);
        QCOMPARE(spyServerPlayerJoined->at(i-startNumClients).at(0), playerNames[i]);

        // Clear all signals
        spyClientConnectResult[i]->clear();
        spyClientError[i]->clear();
        spyClientLoginResult[i]->clear();
        spyClientServerDisconnected[i]->clear();
        spyClientGameTerminated[i]->clear();
    }
    // Wait a bit to see if any other errors occured
    QVERIFY(!spyServerError->wait(100));

    // Clear all server signals
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerJoined->clear();
    spyServerPlayerDisconnected->clear();
}

/**
 * Get the socket of the plyer and create playerNetwork.
 * @param playerName is the name of the Player that should be added. This name must be in the playerNames vecotor.
 */

void testPlayerNetwork::addPlayerNetwork(QString playerName)
{
    QVERIFY(playerNames.contains(playerName));
    int j = playerNames.indexOf(playerName);

    // Clear all server signals
    spyServer->clear();
    spyServerError->clear();
    spyServerPlayerJoined->clear();
    spyServerPlayerDisconnected->clear();

    // Clear the clinet's signals
    spyClientConnectResult[j]->clear();
    spyClientError[j]->clear();
    spyClientLoginResult[j]->clear();
    spyClientServerDisconnected[j]->clear();
    spyClientGameTerminated[j]->clear();

    // Get the client socket and remove it from the server
    QTcpSocket* tempSoc = testServerNetA.getPlayerSoc(playerName);
    QVERIFY(tempSoc != nullptr);

    testPlayerNet.append(new PlayerNetwork(this, playerName, tempSoc));

    // Server should not emit clientDisconnected
    QVERIFY(!spyServerPlayerDisconnected->wait(100));
    QVERIFY(spyServerPlayerDisconnected->count() == 0);
    QVERIFY(spyServer->count() == 0);
    QVERIFY(spyServerError->count() == 0);
    QVERIFY(spyServerPlayerJoined->count() == 0);


    // Client should also not emit anything
    QVERIFY(spyClientConnectResult[j]->count() == 0);
    QVERIFY(spyClientError[j]->count() == 0);
    QVERIFY(spyClientLoginResult[j]->count() == 0);
    QVERIFY(spyClientServerDisconnected[j]->count() == 0);
    QVERIFY(spyClientGameTerminated[j]->count() == 0);

    // Get the last index of the Vector
    int i = testPlayerNet.count() - 1;

    // Setup signals
    spyPlayerGeneralError.append(new QSignalSpy(testPlayerNet[i], SIGNAL(generalError(QString))));
    spyPlayerBidSelected.append(new QSignalSpy(testPlayerNet[i], SIGNAL(bidSelected(Bid))));
    spyPlayerMoveSelected.append(new QSignalSpy(testPlayerNet[i], SIGNAL(moveSelected(Card))));
    spyPlayerMessageGenerated.append(new QSignalSpy(testPlayerNet[i], SIGNAL(messageGenerated(QString))));
    spyPlayerClientDisconnected.append(new QSignalSpy(testPlayerNet[i], SIGNAL(clientDisconnected())));

    // Verify all signals
    QVERIFY(spyPlayerGeneralError[i]->isValid());
    QVERIFY(spyPlayerBidSelected[i]->isValid());
    QVERIFY(spyPlayerMoveSelected[i]->isValid());
    QVERIFY(spyPlayerMessageGenerated[i]->isValid());
    QVERIFY(spyPlayerClientDisconnected[i]->isValid());

}
