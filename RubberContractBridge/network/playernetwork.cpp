#include "playernetwork.h"

/**
 * Constructor
 * @param parent
 */

PlayerNetwork::PlayerNetwork(QObject *parent, QString playerName, QTcpSocket *clientSoc)
{
    PlayerNetwork::playerName = playerName;
    PlayerNetwork::clientSoc = clientSoc;
    idCounter = 1; // One message has been sent by the Client
    prevID = 0; // The first message has been received and the ID was 0, thus prevID is 0.
    gameTerminatedOnce = false; // Only send gameTerminated once to the client. Set to true after gameTerminated has been sent once.

    in.setDevice(PlayerNetwork::clientSoc);
    in.setVersion(QDataStream::Qt_5_10);

    // Make signal connections with the clientSoc
    connect(PlayerNetwork::clientSoc, &QIODevice::readyRead,this, &PlayerNetwork::rxAll);
    connect(PlayerNetwork::clientSoc, &QAbstractSocket::disconnected,this, &PlayerNetwork::internalClientDisconnected);
    // Connection errors
    connect(PlayerNetwork::clientSoc, &QAbstractSocket::errorOccurred, this, &PlayerNetwork::socketError);
}

/**
 * Send notification to the client that it is their turn to bid.
 */

void PlayerNetwork::notifyBidTurn()
{
    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "NOTIFY_BID_TURN";
    txAll(txObj);
}

/**
 * Send notification to the client that it is their turn to make a move.
 */

void PlayerNetwork::notifyMoveTurn()
{
    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "NOTIFY_MOVE_TURN";
    txAll(txObj);
}

/**
 * Send playerGameState to client.
 */

void PlayerNetwork::updateGameState(PlayerGameState gameState)
{
    // Create the QJsonObject for the PlayerGameState
    QJsonObject jsonPlayerState;
    gameState.write(jsonPlayerState);

    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "UPDATE_GAME_STATE";
    txObj["PlayerGameState"] = jsonPlayerState;
    txAll(txObj);
}

/**
 * Send notification that the bid has been rejected.
 * @param reason QString The reason why the bid has been rejected by the server.
 */

void PlayerNetwork::notifyBidRejected(QString reason)
{
    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "NOTIFY_BID_REJECTED";
    txObj["BidRejectReason"] = reason;
    txAll(txObj);
}

/**
 * Send notification that the move has been rejected.
 * @param reason QString The reason why the move has been rejected by the server.
 */

void PlayerNetwork::notifyMoveRejected(QString reason)
{
    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "NOTIFY_MOVE_REJECTED";
    txObj["MoveRejectReason"] = reason;
    txAll(txObj);
}

/**
 * Broadcasted chat message sent to the client.
 * @param source QString Player name of sender.
 * @param msg QString Message content.
 */

void PlayerNetwork::message(QString source, QString msg)
{
    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "MESSAGE";
    txObj["MsgSource"] = source;
    txObj["MsgMessage"] = msg;
    txAll(txObj);
}

/**
 * Transmit this when the game is over, with the reason for the end of the game.
 * @param reason QString Reason why the game has been terminated.
 */

void PlayerNetwork::gameTerminated(QString reason)
{
    if (gameTerminatedOnce == false){
        gameTerminatedOnce = true;

        // Create QJsonObject
        QJsonObject txObj;
        txObj["Type"] = "GAME_TERMINATED";
        txObj["TerminationReason"] = reason;
        txAll(txObj);
    }
}

/**
 * All received data goes through this.
 * The function calls the relevant rx functions, depending on the "Type" received.
 */

void PlayerNetwork::rxAll()
{
    in.startTransaction();
    QJsonObject rxObj;
    in >> rxObj;

    if (!in.commitTransaction()){
        emit generalError("Datastream read error occured. It is suggested to restart the game.");
        qInfo() << "rxAll: Datastream error occured.";
        return;
    }

    // Validate the QJsonObject
    // It should contain a Type field, with valid information in the string part.
    if (rxObj.contains("Type") && rxObj["Type"].isString() && rxObj.contains("ID") && rxObj["ID"].isDouble()){
        // QJsonObject received contained the expected data.
        // Test if ID number is larger than prevID
        if (rxObj["ID"].toInt() <= prevID) {
            emit generalError("Outdated data was received. The data will be ignored.");
            return;
        }

    } else {
        // QJsonObject received had errors (received data will be ignored).
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qInfo() << "rxAll: Data received from server has been incorrectly formatted.";
        return;
    }

    // The data received is valid.
    // Choose the function that will handel the data.
    QString tempStr = rxObj["Type"].toString();
    // Update the prevID
    prevID = rxObj["ID"].toInt();

    if (tempStr == "BID_SEND") {
        rxBidSelected(rxObj);
        return;
    }
    if (tempStr == "MOVE_SEND") {
        rxMoveSelected(rxObj);
        return;
    }
    if (tempStr == "MESSAGE") {
        rxMessage(rxObj);
        return;
    }

    // Default
    emit generalError("An incorrect 'Type' has been received. The data will be ignored.");
}

/*!
 * \brief Signal the server if an socket error occured.
 * \param socError QAbstractSocket::SocketError
 */
void PlayerNetwork::socketError(QAbstractSocket::SocketError socError)
{
    qInfo() << "socketError: A socket error occured in PlayerNetwork: " << socError;

    if (socError != QAbstractSocket::RemoteHostClosedError){
        // Since serverDisconnected is emited when socError == QAbstractSocket::RemoteHostClosedError,
        // don't emit a generalError.
        emit generalError("The following error occurred: " + clientSoc->errorString() + " Restart the game server.");
    }

    // Ensure that the socket has been disconnected.
    clientSoc->abort();
}

/*!
 * \brief Handel all data that is sent to the client.
 * \param data QJsonObject containing at least the "Type" and no "ID" fields.
 */

void PlayerNetwork::txAll(QJsonObject data)
{
    // Cannot send data if not connected to the server.
    if (!clientSoc->isValid()){
        emit generalError("Not connected to the server. Cannot send data to the server.");
        return;
    }

    // Test to see if data that must be sent is valid
    if (!data.contains("Type")){
        emit generalError("Data to be sent does not contain 'Type' field. Data was not sent.");
        return;
    }

    if (data.contains("ID")) {
        emit generalError("Data to be sent should not contain an 'ID' field. 'ID' field was removed.");
        data.remove("ID");
    }

    // Add the ID field to the QJsonObject
    data["ID"] = idCounter++;

    // Create transmitting communication data stream
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    // Add delay to give time for previous data sent to be received by the client
    qint64 timeNow = QDateTime::currentMSecsSinceEpoch() + 200; // Add 100ms
    while(timeNow > QDateTime::currentMSecsSinceEpoch()){
         QCoreApplication::processEvents(QEventLoop::AllEvents);
    }

    // Send the login request to the server
    out << data;
    int tempVal = clientSoc->write(block);
    clientSoc->waitForBytesWritten(tempVal);

    qInfo() << "txAll: Number of bytes sent to client: " << tempVal;

    if (tempVal == -1 || tempVal < block.size()) {
        // An error occured when writing the data block.
        // OR The block written was too small (did not contain enough bytes).
        emit generalError("An error occured with sending data to the client. It is suggested to restart the game.");
    }
}

/**
 * Send bid made by the client to the server.
 * @param bidObj QJsonObject with "Type" = "BID_SEND".
 */

void PlayerNetwork::rxBidSelected(QJsonObject bidObj)
{
    // Validate the QJsonObject
    if (!bidObj.contains("Bid") || !bidObj["Bid"].isObject()){
        // QJsonObject received had errors (received data will be ignored).
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qInfo() << "rxBidSelected: Data received from server has been incorrectly formatted.";
        return;
    }

    // Get the QJsonObject that contains the Bid data
    QJsonObject jsonBid = bidObj["Bid"].toObject();

    // Convert to QJsonOnject to Bid
    Bid rxBid;
    rxBid.read(jsonBid);

    emit bidSelected(rxBid);
}

/**
 * Send move selected by the client to the server.
 * @param moveObj QJsonObject with "Type" = "MOVE_SEND".
 */

void PlayerNetwork::rxMoveSelected(QJsonObject moveObj)
{
    // Validate the QJsonObject
    if (!moveObj.contains("Card") || !moveObj["Card"].isObject()){
        // QJsonObject received had errors (received data will be ignored).
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qInfo() << "rxMoveSelected: Data received from server has been incorrectly formatted.";
        return;
    }

    // Get the QJsonObject that contains the Card data
    QJsonObject jsonCard = moveObj["Card"].toObject();

    // Convert to QJsonOnject to Card
    Card rxCard;
    rxCard.read(jsonCard);

    emit moveSelected(rxCard);
}

/**
 * Broadcasted chat message received from the client.
 * \param msgObj QJsonObject with "Type" = "MESSAGE".
 */

void PlayerNetwork::rxMessage(QJsonObject msgObj)
{
    // Validate the QJsonObject
    if (!msgObj.contains("Message") || !msgObj["Message"].isString()){
        // QJsonObject received had errors (received data will be ignored).
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qInfo() << "rxMessage: Data received from server has been incorrectly formatted.";
        return;
    }

    emit messageGenerated(msgObj["Message"].toString());
}

/**
 * Inform the server that the client has disconnected.
 * The server should terminate the game and inform all the other players of the reason for disconnection.
 * It is the Server's responsibility to delete the class and not call any functions on this class.
 */

void PlayerNetwork::internalClientDisconnected()
{
    // Ensure that the client is actually disconnected
    if (gameTerminatedOnce == false) {
        emit clientDisconnected();
        gameTerminatedOnce = true;
    }
    clientSoc->abort();

    // Prevent the socket from being aborted or deleted again
    clientSoc = nullptr;
}
