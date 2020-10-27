#include "playernetwork.h"

PlayerNetwork::PlayerNetwork(QObject *parent, QString playerName, QTcpSocket *clientSoc)
{
    // Once ingerited, init the playerName.
    PlayerNetwork::playerName = playerName;
    PlayerNetwork::clientSoc = clientSoc;
    idCounter = 1; // One message has been sent by the
    prevID = 0; // The first message has been received and the ID was 0, thus prevID is 0.

    in.setDevice(PlayerNetwork::clientSoc);
    in.setVersion(QDataStream::Qt_5_10);

    // Make signal connections with the clientSoc
    connect(PlayerNetwork::clientSoc, &QIODevice::readyRead,this, &PlayerNetwork::rxAll);
    connect(PlayerNetwork::clientSoc, &QAbstractSocket::disconnected,this, &PlayerNetwork::internalClientDisconnected);
    // Connection errors
    connect(PlayerNetwork::clientSoc, &QAbstractSocket::errorOccurred, this, &PlayerNetwork::socketError);

    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);

}

/**
 * Destructor
 */

PlayerNetwork::~PlayerNetwork()
{
    if (clientSoc != nullptr){
        clientSoc->abort();
        clientSoc->deleteLater();
    }
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

}

/**
 * Send notification that the move has been rejected.
 * @param reason QString The reason why the move has been rejected by the server.
 */

void PlayerNetwork::notifyMoveRejected(QString reason)
{

}

/**
 * Broadcasted chat message sent to the client.
 * @param source QString Player name of sender.
 * @param msg QString Message content.
 */

void PlayerNetwork::message(QString source, QString msg)
{

}

/**
 * Transmit this when the game is over, with the reason for the end of the game.
 * @param reason QString Reason why the game has been terminated.
 */

void PlayerNetwork::gameTerminated(QString reason)
{

}

QVector<bool> PlayerNetwork::getUnitTest() const
{
    return bUnitTest;
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
        qWarning() << "Datastream error occured.";
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
        qWarning() << "Data received from server has been incorrectly formatted.";
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
    return;
}

/*!
 * \brief Signal the server if an socket error occured.
 * \param socError QAbstractSocket::SocketError
 */
void PlayerNetwork::socketError(QAbstractSocket::SocketError socError)
{
    qInfo() << "A socket error occured in PlayerNetwork: " << socError;

    emit generalError("The following error occurred: " + clientSoc->errorString() + " Restart the game server.");

//    clientSoc->abort();
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

    // Send the login request to the server
    out << data;
    int tempVal = clientSoc->write(block);

    qInfo() << "Number of bytes expected to be sent to the client: " << block.size();
    qInfo() << "Number of bytes sent to client: " << tempVal;

    if (tempVal == -1) {
        // An error occured when writing the data block
        emit generalError("An error occured with sending data to the client. It is suggested to restart the game.");
    } else if (tempVal < block.size()) {
        // The block written was too small (did not contain enough bytes).
        emit generalError("An error occured with sending data to the client. It is suggested to restart the game.");
    }
}

void PlayerNetwork::rxBidSelected(QJsonObject bidObj)
{

}

void PlayerNetwork::rxMoveSelected(QJsonObject moveObj)
{

}

void PlayerNetwork::rxMessage(QJsonObject msgObj)
{

}

/**
 * Inform the server that the client has disconnected.
 * The server should terminate the game and inform all the other players of the reason for disconnection.
 * It is the Server's responsibility to delete the class and not call any functions on this class.
 */

void PlayerNetwork::internalClientDisconnected()
{
    // Ensure that the client is actually disconnected
    emit clientDisconnected();
    clientSoc->abort();
    clientSoc->deleteLater();
}
