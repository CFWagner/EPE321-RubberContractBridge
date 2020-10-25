#include "playernetwork.h"

//PlayerNetwork::PlayerNetwork(QObject *parent, QString playerName, QTcpSocket *clientSoc) : QObject(parent)
//{
//    // Once ingerited, init the playerName.
//    PlayerNetwork::playerName = playerName;
//    PlayerNetwork::clientSoc = clientSoc;

//}

PlayerNetwork::PlayerNetwork(QObject *parent, QString playerName, QTcpSocket *clientSoc)
{
    // Once ingerited, init the playerName.
    PlayerNetwork::playerName = playerName;
    PlayerNetwork::clientSoc = clientSoc;
    idCounter = 0;
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

PlayerNetwork::~PlayerNetwork()
{

}

void PlayerNetwork::notifyBidTurn()
{

}

void PlayerNetwork::notifyMoveTurn()
{

}

void PlayerNetwork::updateGameState(PlayerGameState gameState)
{

}

void PlayerNetwork::notifyBidRejected(QString reason)
{

}

void PlayerNetwork::notifyMoveRejected(QString reason)
{

}

void PlayerNetwork::message(QString source, QString msg)
{

}

void PlayerNetwork::gameTerminated(QString reason)
{

}

QVector<bool> PlayerNetwork::getUnitTest() const
{
    return bUnitTest;
}

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
        // QJsonObject received had errors
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qWarning() << "Data received from server has been incorrectly formatted.";

        // TODO: Handel case where data received was incorrect.
        // If not logged in, dissconnect and signal GUI

        // If logged in, request a resend of the data? Or ignaor it, or stop the client.
        // Maybe have a last message detail on server side?

        return;
    }

    // The data received is valid.
    // Choose the function that will handel the data.
    QString tempStr = rxObj["Type"].toString();
    if (tempStr == "NOTIFY_BID_TURN") {
        rxNotifyBidTurn();
        return;
    }
    if (tempStr == "NOTIFY_MOVE_TRUN") {
        rxNotifyMoveTurn();
        return;
    }
    if (tempStr == "NOTIFY_BID_REJECTED") {
        rxNotifyBidRejected(rxObj);
        return;
    }
    if (tempStr == "NOTIFY_MOVE_REJECTED") {
        rxNotifyMoveRejected(rxObj);
        return;
    }
    if (tempStr == "LOGIN_RESULT") {
        rxLoginResult(rxObj);
        return;
    }
    if (tempStr == "UPDATE_GAME_STATE") {
        rxUpdateGameState(rxObj);
        return;
    }
    if (tempStr == "MESSAGE") {
        rxMessage(rxObj);
        return;
    }
    if (tempStr == "GAME_TERMINATED") {
        rxGameTerminated(rxObj);
        return;
    }
    if (tempStr == "PING_RECEIVED") {
        rxPingReceived();
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

    emit generalError("The following error occurred: " + clientSoc->errorString());

    clientSoc->abort();
}


void PlayerNetwork::txAll(QJsonObject data)
{

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

void PlayerNetwork::rxPingReturn()
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
