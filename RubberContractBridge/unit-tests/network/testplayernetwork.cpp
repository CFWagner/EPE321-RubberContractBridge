#include "testplayernetwork.h"

/**
 * Constructor
 * @param parent
 */

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
    // Add Clients - Comment on what tests the clients are used for.
    addManyClients(4); // General tests
    addManyClients(1); // disconnectClientFromServerAfterGameStarted tests
    addManyClients(2); // testStopListening

    // Do not change the number or order of the addPlayerNetwork calls, since it will break all following tests.
    for (int i = 0; i < 4; i++){
        addPlayerNetwork(playerNames[i]);
    }

    // Get the socket used in disconnectClientFromServerAfterGameStarted
    int k = 4;

    // Reference to Player's QTcpSocket
    testPlayerSocket = new QTcpSocket*;

    // Add a 5th player and get the PlayerSocket
    addPlayerNetwork(playerNames[k], testPlayerSocket);
}

/**
 * Test that all players still in the lobby is disconnected after stopListening is called.
 */

void testPlayerNetwork::testStopListeningClientDisconnection()
{
    // The server should stop listening for new logon attempts
    testServerNetA.stopListening();

    // Calling the following function should make the test fail
    // addManyClients(1);

    // Detect the serverDisconnected signals emitted form the clients that was still in the lobby
    // Wait long enought for both clients to be disconnected.
    // spyClientServerDisconnected[4] should emmited. Thus it will wait full 100ms.
    QVERIFY(!spyClientServerDisconnected[4]->wait(100));

    // The following clients were still in the lobby and should be disconnected
    for (int k = 5; k < 7; k++){
        QCOMPARE(spyClientServerDisconnected[k]->count(), 1);
        spyClientServerDisconnected[k]->clear();
    }

    // No other errors should have occured
    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();
}

/**
 * Start a game and then disconnect the client (from the server side).
 * Then test if the correct client emits gameTerminated.
 */

void testPlayerNetwork::disconnectClientFromServerAfterGameStarted()
{
    int k = 4;

    // Start the game by sending a PlayerGameState
    // updateGameState
    // Create Player game state
    PlayerGameState originalPlayerGameState = generatePlayerGameState();

    testPlayerNet[k]->updateGameState(originalPlayerGameState);
    QVERIFY(spyClientUpdateGameState[k]->wait(100));
    QCOMPARE(spyClientUpdateGameState[k]->count(), 1);
    QCOMPARE(qvariant_cast<PlayerGameState>(spyClientUpdateGameState[k]->at(0).at(0)), originalPlayerGameState);
    spyClientUpdateGameState[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // Emulate server disconnection by aborting the QTcpSocket of the player.
    (*testPlayerSocket)->abort();

    QVERIFY(spyClientGameTerminated[k]->wait(100));
    QCOMPARE(spyClientGameTerminated[k]->count(), 1);
    QCOMPARE(spyClientGameTerminated[k]->at(0).at(0).toString(), "Client lost connection to the server.");
    spyClientGameTerminated[k]->clear();

    // On the player side check the clientDisconnected signal
    QCOMPARE(spyPlayerClientDisconnected[k]->count(), 1);
    spyPlayerClientDisconnected[k]->clear();

    // None of the other Clients were disconnected.
    // The serverDisconnected signal (of the player that was aborted above) should not have been emitted.
    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();
}

/**
 * Test that all transmit functions and receive signals are operating correctly.
 * This is communication from PlayerNetwork to ClientNetwork.
 */

void testPlayerNetwork::testCommunicationsToClient()
{
    int k = 0;
    // PlayerNetwork to ClientNetwork

    // notifyBidTurn
    k = 0;
    testPlayerNet[k]->notifyBidTurn();
    QVERIFY(spyClientNotifyBidTurn[k]->wait(100));
    QCOMPARE(spyClientNotifyBidTurn[k]->count(), 1);
    spyClientNotifyBidTurn[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // notifyMoveTurn
    k = 0;
    testPlayerNet[k]->notifyMoveTurn();
    QVERIFY(spyClientNotifyMoveTurn[k]->wait(100));
    QCOMPARE(spyClientNotifyMoveTurn[k]->count(), 1);
    spyClientNotifyMoveTurn[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // notifyBidRejected
    k = 0;
    QString rejectReason = "The bid was rejected because of this very long and ambigious reason. "
                           "But just to use !@#$%^&*() and \"n\" and a \nnew line we should add 10X+9Y=5Z";
    testPlayerNet[k]->notifyBidRejected(rejectReason);
    QVERIFY(spyClientNotifyBidRejected[k]->wait(100));
    QCOMPARE(spyClientNotifyBidRejected[k]->count(), 1);
    QCOMPARE(spyClientNotifyBidRejected[k]->at(0).at(0).toString(), rejectReason);
    spyClientNotifyBidRejected[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // notifyMoveRejected
    k = 0;

    // Make reject reason unique by adding text
    rejectReason += "Extra text";

    testPlayerNet[k]->notifyMoveRejected(rejectReason);
    QVERIFY(spyClientNotifyMoveRejected[k]->wait(100));
    QCOMPARE(spyClientNotifyMoveRejected[k]->count(), 1);
    QCOMPARE(spyClientNotifyMoveRejected[k]->at(0).at(0).toString(), rejectReason);
    spyClientNotifyMoveRejected[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // updateGameState
    k = 0;

    // Create Player game state
    PlayerGameState originalPlayerGameState = generatePlayerGameState();

    testPlayerNet[k]->updateGameState(originalPlayerGameState);
    QVERIFY(spyClientUpdateGameState[k]->wait(100));
    QCOMPARE(spyClientUpdateGameState[k]->count(), 1);
    QCOMPARE(qvariant_cast<PlayerGameState>(spyClientUpdateGameState[k]->at(0).at(0)), originalPlayerGameState);
    spyClientUpdateGameState[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // message
    k = 0;

    // Make reject reason unique by adding text
    QString sourceName = playerNames[1];
    QString messageContent = "This is a message sent from me.";

    testPlayerNet[k]->message(sourceName, messageContent);
    QVERIFY(spyClientMessageReceived[k]->wait(100));
    QCOMPARE(spyClientMessageReceived[k]->count(), 1);
    QCOMPARE(spyClientMessageReceived[k]->at(0).at(0).toString(), sourceName);
    QCOMPARE(spyClientMessageReceived[k]->at(0).at(1).toString(), messageContent);
    spyClientMessageReceived[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // gameTerminated
    k = 0;
    QString terminationReason = "The game 123 was terminated for no apparent reason. "
                                "Just kidding, nothing was terminated, since this is just a test. "
                                "How fast can I type very long reasons out?";

    testPlayerNet[k]->gameTerminated(terminationReason);
    QVERIFY(spyClientGameTerminated[k]->wait(100));
    QCOMPARE(spyClientGameTerminated[k]->count(), 1);
    QCOMPARE(spyClientGameTerminated[k]->at(0).at(0).toString(), terminationReason);
    spyClientGameTerminated[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();
}

/**
 * Test that all transmit functions and receive signals are operating correctly.
 * This is communication from ClientNetwork to PlayerNetwork.
 */

void testPlayerNetwork::testCommunicationsFromClient()
{
    int k = 0;
    // ClientNetwork to PlayerNetwork

    // txBidSelected
    k = 0;

    // Create Bid
    Bid originalBid = generateBid();

    // Connect signal
    connect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);
    emit emitTxBidSelected(originalBid);
    disconnect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);

    // Validate response
    QVERIFY(spyPlayerBidSelected[k]->wait(100));
    QCOMPARE(spyPlayerBidSelected[k]->count(), 1);
    QCOMPARE(qvariant_cast<Bid>(spyPlayerBidSelected[k]->at(0).at(0)), originalBid);
    spyPlayerBidSelected[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // txMoveSelected
    k = 0;

    // Create Card
    Card originalCard = generateCard();

    // Connect signal
    connect(this, &testPlayerNetwork::emitTxMoveSelected, testClientNet[k], &ClientNetwork::txMoveSelected);
    emit emitTxMoveSelected(originalCard);
    disconnect(this, &testPlayerNetwork::emitTxMoveSelected, testClientNet[k], &ClientNetwork::txMoveSelected);

    // Validate response
    QVERIFY(spyPlayerMoveSelected[k]->wait(100));
    QCOMPARE(spyPlayerMoveSelected[k]->count(), 1);
    QCOMPARE(qvariant_cast<Card>(spyPlayerMoveSelected[k]->at(0).at(0)), originalCard);
    spyPlayerMoveSelected[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // txMessage
    k = 0;

    // Make reject reason unique by adding text
    QString messageContent = "This is a message sent from " + playerNames[k];

    // Connect signal
    connect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);
    emit emitTxMessage(messageContent);
    disconnect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);

    // Validate response
    QVERIFY(spyPlayerMessageGenerated[k]->wait(100));
    QCOMPARE(spyPlayerMessageGenerated[k]->count(), 1);
    QCOMPARE(spyPlayerMessageGenerated[k]->at(0).at(0).toString(), messageContent);
    spyPlayerMessageGenerated[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();
}

/**
 * Test repetitive communication and to multiple clients.
 * This includes PlayerNetwork to ClientNetwork and ClientNetwork to PlayerNetwork communication.
 */

void testPlayerNetwork::testRepetitiveCommunication()
{
    int k = 0;
    // PlayerNetwork to ClientNetwork

    // Repeat the test many times
    for (int j = 0; j < 10; j++){

        // notifyBidTurn
        k = 0;
        testPlayerNet[k]->notifyBidTurn();
        QVERIFY(spyClientNotifyBidTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyBidTurn[k]->count(), 1);
        spyClientNotifyBidTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyMoveTurn
        k = 0;
        testPlayerNet[k]->notifyMoveTurn();
        QVERIFY(spyClientNotifyMoveTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyMoveTurn[k]->count(), 1);
        spyClientNotifyMoveTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyBidTurn
        k = 3;
        testPlayerNet[k]->notifyBidTurn();
        QVERIFY(spyClientNotifyBidTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyBidTurn[k]->count(), 1);
        spyClientNotifyBidTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyMoveTurn
        k = 2;
        testPlayerNet[k]->notifyMoveTurn();
        QVERIFY(spyClientNotifyMoveTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyMoveTurn[k]->count(), 1);
        spyClientNotifyMoveTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyBidTurn
        k = 3;
        testPlayerNet[k]->notifyBidTurn();
        QVERIFY(spyClientNotifyBidTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyBidTurn[k]->count(), 1);
        spyClientNotifyBidTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyMoveTurn
        k = 1;
        testPlayerNet[k]->notifyMoveTurn();
        QVERIFY(spyClientNotifyMoveTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyMoveTurn[k]->count(), 1);
        spyClientNotifyMoveTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();

        // notifyMoveTurn
        k = 1;
        testPlayerNet[k]->notifyMoveTurn();
        QVERIFY(spyClientNotifyMoveTurn[k]->wait(100));
        QCOMPARE(spyClientNotifyMoveTurn[k]->count(), 1);
        spyClientNotifyMoveTurn[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();
    }

    // Send a large amount of data repetitavely
    for (int i = 0; i < 50; i++){
        // updateGameState
        k = 2;

        // Create Player game state
        PlayerGameState originalPlayerGameState = generatePlayerGameState();

        testPlayerNet[k]->updateGameState(originalPlayerGameState);
        QVERIFY(spyClientUpdateGameState[k]->wait(100));
        QCOMPARE(spyClientUpdateGameState[k]->count(), 1);
        QCOMPARE(qvariant_cast<PlayerGameState>(spyClientUpdateGameState[k]->at(0).at(0)), originalPlayerGameState);
        spyClientUpdateGameState[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();
    }

    // ClientNetwork to PlayerNetwork

    for (int j = 0; j < 10; j++){
        for (int k = 0; k < 4; k++){
            // txBidSelected
            // Create Bid
            Bid originalBid = generateBid();

            // Connect signal
            connect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);
            emit emitTxBidSelected(originalBid);
            disconnect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);

            // Validate response
            QVERIFY(spyPlayerBidSelected[k]->wait(100));
            QCOMPARE(spyPlayerBidSelected[k]->count(), 1);
            QCOMPARE(qvariant_cast<Bid>(spyPlayerBidSelected[k]->at(0).at(0)), originalBid);
            spyPlayerBidSelected[k]->clear();

            checkAllCientSignals();
            checkAllPlayerSignals();
            checkAllServerSignals();
        }

        for (int j = 0; j < 3; j++){
            // txMoveSelected
            k = 3;

            // Create Card
            Card originalCard = generateCard();

            // Connect signal
            connect(this, &testPlayerNetwork::emitTxMoveSelected, testClientNet[k], &ClientNetwork::txMoveSelected);
            emit emitTxMoveSelected(originalCard);
            disconnect(this, &testPlayerNetwork::emitTxMoveSelected, testClientNet[k], &ClientNetwork::txMoveSelected);

            // Validate response
            QVERIFY(spyPlayerMoveSelected[k]->wait(100));
            QCOMPARE(spyPlayerMoveSelected[k]->count(), 1);
            QCOMPARE(qvariant_cast<Card>(spyPlayerMoveSelected[k]->at(0).at(0)), originalCard);
            spyPlayerMoveSelected[k]->clear();

            checkAllCientSignals();
            checkAllPlayerSignals();
            checkAllServerSignals();
        }

        // txBidSelected
        int k = 2;

        // Create Bid
        Bid originalBid = generateBid();

        // Connect signal
        connect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);
        emit emitTxBidSelected(originalBid);
        disconnect(this, &testPlayerNetwork::emitTxBidSelected, testClientNet[k], &ClientNetwork::txBidSelected);

        // Validate response
        QVERIFY(spyPlayerBidSelected[k]->wait(100));
        QCOMPARE(spyPlayerBidSelected[k]->count(), 1);
        QCOMPARE(qvariant_cast<Bid>(spyPlayerBidSelected[k]->at(0).at(0)), originalBid);
        spyPlayerBidSelected[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();
    }

    // Send a large amount of data repetitavely
    for (int i = 0; i < 50; i++){
        // txMessage
        int k = 1;

        // Make reject reason unique by adding text
        QString messageContent = "This is a message sent from " + playerNames[k] +
                " with a lot of other data sent with this one message. "
                "Do not send such long messages, since you are supposed to be focuesd on the game!";

        // Connect signal
        connect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);
        emit emitTxMessage(messageContent);
        disconnect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);

        // Validate response
        QVERIFY(spyPlayerMessageGenerated[k]->wait(100));
        QCOMPARE(spyPlayerMessageGenerated[k]->count(), 1);
        QCOMPARE(spyPlayerMessageGenerated[k]->at(0).at(0).toString(), messageContent);
        spyPlayerMessageGenerated[k]->clear();

        checkAllCientSignals();
        checkAllPlayerSignals();
        checkAllServerSignals();
    }
}

/**
 * Force a situation where a datastream error will occur.
 * Then test if the correct signals was transmitted.
 * Check if data can successfully be transmitted after a datastream error occured.
 */

void testPlayerNetwork::testErrors()
{
    int k = 0;
    // PlayerNetwork to ClientNetwork

    // gameTerminated
    k = 0;
    QString terminationReason = "The game 123 was terminated for no apparent reason. "
                                "Just kidding, nothing was terminated, since this is just a test. "
                                "How fast can I type very long reasons out?";

    // Transmit too much data for the datastream to handel
    for (int j = 0; j < 9; j++){
        terminationReason += terminationReason;
    }

    testPlayerNet[k]->gameTerminated(terminationReason);
    QVERIFY(spyClientGameTerminated[k]->wait(100));
    QCOMPARE(spyClientGameTerminated[k]->count(), 1);
    // The following test works, but not sure that it will always work.
    // The idea is to restart the server once a datastream error has occured, so this test does not matter.
//    QCOMPARE(spyClientGameTerminated[k]->at(0).at(0).toString(), terminationReason);
    spyClientGameTerminated[k]->clear();

    // Catch errors on the Client side
    QCOMPARE(spyClientError[k]->count(), 1);
    QCOMPARE(spyClientError[k]->at(0).at(0).toString(), "Datastream read error occured. It is suggested to restart the game.");
    spyClientError[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();


    // Test to see if next transmission will work after an datastream error has occured
    // gameTerminated
    k = 0;
    QString terminationReason2 = "The game 123 was terminated for no apparent reason. "
                                "Just kidding, nothing was terminated, since this is just a test. "
                                "How fast can I type very long reasons out?";

    // Transmit just less than too much data for the datastream to handel
    for (int j = 0; j < 8; j++){
        terminationReason2 += terminationReason2;
    }

    testPlayerNet[k]->gameTerminated(terminationReason2);
    QVERIFY(spyClientGameTerminated[k]->wait(100));
    QCOMPARE(spyClientGameTerminated[k]->count(), 1);
    QCOMPARE(spyClientGameTerminated[k]->at(0).at(0).toString(), terminationReason2);
    spyClientGameTerminated[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // ClientNetwork to PlayerNetwork

    // txMessage
    k = 0;

    // Connect signal
    connect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);
    emit emitTxMessage(terminationReason);
    disconnect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);

    // Validate response
    QVERIFY(spyPlayerMessageGenerated[k]->wait(100));
    QCOMPARE(spyPlayerMessageGenerated[k]->count(), 1);
    // The following test works, but not sure that it will always work.
    // The idea is to restart the server once a datastream error has occured, so this test does not matter.
//    QCOMPARE(spyPlayerMessageGenerated[k]->at(0).at(0).toString(), terminationReason);
    spyPlayerMessageGenerated[k]->clear();

    // Catch errors on the Player side
    QCOMPARE(spyPlayerGeneralError[k]->count(), 1);
    QCOMPARE(spyPlayerGeneralError[k]->at(0).at(0).toString(), "Datastream read error occured. It is suggested to restart the game.");
    spyPlayerGeneralError[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();

    // Test to see if next transmission will work after an datastream error has occured
    // txMessage
    k = 0;

    // Connect signal
    connect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);
    emit emitTxMessage(terminationReason2);
    disconnect(this, &testPlayerNetwork::emitTxMessage, testClientNet[k], &ClientNetwork::txMessage);

    // Validate response
    QVERIFY(spyPlayerMessageGenerated[k]->wait(100));
    QCOMPARE(spyPlayerMessageGenerated[k]->count(), 1);
    QCOMPARE(spyPlayerMessageGenerated[k]->at(0).at(0).toString(), terminationReason2);
    spyPlayerMessageGenerated[k]->clear();

    checkAllCientSignals();
    checkAllPlayerSignals();
    checkAllServerSignals();
}

/**
 * Delete all memory allocated
 */

void testPlayerNetwork::cleanupTestCase()
{
    // Ensure that all QSignalSpy objects are deleted.

    spyServer->deleteLater();
    spyServerPlayerJoined->deleteLater();
    spyServerError->deleteLater();
    spyServerPlayerDisconnected->deleteLater();

    for (int i = 0; i < testClientNet.count(); i++){
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

    // Test player signals when client unexpectedly disconnects
    QVERIFY(!spyPlayerGeneralError[0]->wait(100)); // No general error present
    QCOMPARE(spyPlayerClientDisconnected[0]->count(), 1); // Client disconnected error present

    for (int i = 0; i < testPlayerNet.count(); i++){
       spyPlayerGeneralError[i]->deleteLater();
       spyPlayerBidSelected[i]->deleteLater();
       spyPlayerMoveSelected[i]->deleteLater();
       spyPlayerMessageGenerated[i]->deleteLater();
       spyPlayerClientDisconnected[i]->deleteLater();

       testPlayerNet[i]->deleteLater();
    }

   // delete memory allocated
   delete testPlayerSocket;
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

        // Create connection with txRequestLogin slot
        connect(this, &testPlayerNetwork::emitTxRequestLogin, testClientNet[i], &ClientNetwork::txRequestLogin);
        emit emitTxRequestLogin(ip,port,playerNames[i],passwordServer);
        disconnect(this, &testPlayerNetwork::emitTxRequestLogin, testClientNet[i], &ClientNetwork::txRequestLogin);

        // Wait
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

void testPlayerNetwork::addPlayerNetwork(QString playerName, QTcpSocket** returnPlayerSocket)
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

    // Since QVERIFY does not allow a non-void function, return the playerSocket by storing it in the variable refenced,
    // unless the default nullptr is given.
    if (returnPlayerSocket != nullptr){
        *returnPlayerSocket = tempSoc;
    }

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

/**
 * Check that no clients emmited any siganls
 */

void testPlayerNetwork::checkAllCientSignals()
{
    for (int i = 0; i < testClientNet.count(); i++){
        QCOMPARE(spyClientConnectResult[i]->count(),0);
        QCOMPARE(spyClientError[i]->count(),0);
        QCOMPARE(spyClientLoginResult[i]->count(),0);
        QCOMPARE(spyClientServerDisconnected[i]->count(),0);
        QCOMPARE(spyClientGameTerminated[i]->count(),0);
        QCOMPARE(spyClientNotifyBidTurn[i]->count(),0);
        QCOMPARE(spyClientNotifyMoveTurn[i]->count(),0);
        QCOMPARE(spyClientNotifyBidRejected[i]->count(),0);
        QCOMPARE(spyClientNotifyMoveRejected[i]->count(),0);
        QCOMPARE(spyClientUpdateGameState[i]->count(),0);
        QCOMPARE(spyClientMessageReceived[i]->count(),0);
    }
}

/**
 * Check that no players emmited any siganls
 */

void testPlayerNetwork::checkAllPlayerSignals()
{
    for (int i = 0; i < testPlayerNet.count(); i++){
        QCOMPARE(spyPlayerGeneralError[i]->count(),0);
        QCOMPARE(spyPlayerBidSelected[i]->count(),0);
        QCOMPARE(spyPlayerMoveSelected[i]->count(),0);
        QCOMPARE(spyPlayerMessageGenerated[i]->count(),0);
        QCOMPARE(spyPlayerClientDisconnected[i]->count(),0);
    }
}

/**
 * Check that the server did not emmit any siganls
 */

void testPlayerNetwork::checkAllServerSignals()
{
    QCOMPARE(spyServerPlayerDisconnected->count(), 0);
    QCOMPARE(spyServer->count(), 0);
    QCOMPARE(spyServerError->count(), 0);
    QCOMPARE(spyServerPlayerJoined->count(), 0);
}

/**
 * Generate a PlayerGameState object with game data inside.
 * @return PlayerGameState initialized to typical values.
 */

PlayerGameState testPlayerNetwork::generatePlayerGameState()
{
    // Initialise attributes
    GamePhase phase = BIDDING;
    Bid* currentBid = nullptr;
    Bid* contractBid = nullptr;
    qint8 gameNumber = 1;
    qint8 dealNumber = 0;
    qint8 trickNumber = 0;
    QVector<CardSet> tricks;
    qint8 tricksWon[4] = {0, 0, 0, 0};
    PlayerPosition playerTurn = NORTH;
    PlayerPosition handToPlay = NORTH;
    PlayerPosition dealer = NORTH;
    PlayerPosition declarer = NORTH;
    Score score;
    GameEvent gameEvent = PLAY_START;
    QMap<PlayerPosition, QString> playerPositions;
    QMap<PlayerPosition, qint8> playerCardCount;
    CardSet playerHand;
    CardSet dummyHand;

    // Populate list attributes
    CardSet trick1;
    trick1.addCard(Card(SPADES, ACE));
    trick1.addCard(Card(HEARTS, ACE));
    trick1.addCard(Card(CLUBS, ACE));
    trick1.addCard(Card(DIAMONDS, TWO));

    CardSet trick2;
    trick2.addCard(Card(SPADES, TWO));
    trick2.addCard(Card(HEARTS, TWO));
    trick2.addCard(Card(CLUBS, TWO));
    trick2.addCard(Card(DIAMONDS, ACE));

    tricks.append(trick1);
    tricks.append(trick2);

    playerHand.addCard(Card(SPADES, THREE));
    playerHand.addCard(Card(HEARTS, THREE));
    playerHand.addCard(Card(CLUBS, THREE));
    playerHand.addCard(Card(DIAMONDS, THREE));

    dummyHand.addCard(Card(SPADES, FOUR));
    dummyHand.addCard(Card(HEARTS, FOUR));
    dummyHand.addCard(Card(CLUBS, FOUR));
    dummyHand.addCard(Card(DIAMONDS, FOUR));

    playerPositions.insert(NORTH, "Player 1");
    playerPositions.insert(EAST, "Player 2");
    playerPositions.insert(SOUTH, "Player 3");
    playerPositions.insert(WEST, "Player 4");

    playerCardCount.insert(NORTH, 4);
    playerCardCount.insert(EAST, 4);
    playerCardCount.insert(SOUTH, 4);
    playerCardCount.insert(WEST, 4);

    currentBid = new Bid(NORTH, SPADES, 5);
    contractBid = new Bid(SOUTH, HEARTS, 2);

    // Construct PlayerGameState instance
    PlayerGameState playerState3(phase, currentBid, contractBid, gameNumber, dealNumber,
                                trickNumber, tricks, tricksWon, playerTurn, handToPlay, dealer, declarer,
                                score, gameEvent, playerPositions, playerCardCount,
                                playerHand, dummyHand);
    return playerState3;
}

/**
 * Generate a Bid object with game data inside.
 * @return Bid initialized to typical values.
 */

Bid testPlayerNetwork::generateBid()
{
    // Construct Bid object with valid constructor arguments when call is not BID
    // Invalid arguments not possible due to enums.
    PlayerPosition bidder = NORTH;
    CardSuit trumpSuit = HEARTS;
    qint8 tricksAbove = 3;

    return Bid(bidder, trumpSuit, tricksAbove);
}

/**
 * Generate a Card object with game data inside.
 * @return Card initialized to typical values.
 */

Card testPlayerNetwork::generateCard()
{
    // Construct Card object with valid constructor arguments.
    // Invalid arguments not possible due to enums.
    CardSuit suit = CLUBS;
    CardRank rank = SEVEN;

    return Card(suit, rank);

}
