#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    // Init internal variables
    gameStarted = false;
    playerName = "";
    keepAlive = nullptr;
    tcpSoc = nullptr;
    tempPlayerName = "";
    tempPassword = "";
    bLoggedIn = false;
    idCounter = 0;
    prevID = -1; // First ID received from server is 0. prevID should be smaller, thus -1.

    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);

    //socketError can use 0 - 4
    //txRequestLogin can use 5 - 9
    //socketConnected can use 10 - 19
    //rxAll can use 20 - 29

    // Prepare the tcpSoc and datastream
    tcpSoc = new QTcpSocket(this);

    in.setDevice(tcpSoc);
    in.setVersion(QDataStream::Qt_5_10);

    // Create connections
    // All reception
    connect(tcpSoc, &QIODevice::readyRead, this, &ClientNetwork::rxAll);
    // Connection errors
    connect(tcpSoc, &QAbstractSocket::errorOccurred, this, &ClientNetwork::socketError);
    // Sucsessfully connected
    connect(tcpSoc, &QAbstractSocket::connected, this, &ClientNetwork::socketConnected);
}

ClientNetwork::~ClientNetwork()
{
    tcpSoc->abort();
}

QVector<bool> ClientNetwork::getUnitTest() const
{
    return bUnitTest;
}

void ClientNetwork::txRequestLogin(QHostAddress serverIP, qint16 port, QString playerName, QString password)
{
    // Connect to the server.

    // Prepare bUnitTest
    for (int i = 5; i <= 9; i++){
        bUnitTest[i] = false;
    }

    // Cannot Request a new login while connected to the host?
    if (tcpSoc->state() != QAbstractSocket::UnconnectedState){
        emit connectionResult(3, "");
        return;
    }

    // Store playerName and password for use after port connected.
    tempPlayerName = playerName;
    tempPassword = password;

    // If connection has already been made, abort it.
    tcpSoc->abort();
    tcpSoc->connectToHost(serverIP, port);

    // socketConnected or socketError will be signaled next, depending on connectToHost()'s outcome.

    qInfo() << "Attempt to connect to the host with server IP: " << serverIP.toString() << " and port: " << port;

}

void ClientNetwork::txBidSelected(Bid bid)
{

}

void ClientNetwork::txMoveSelected(Card card)
{

}

void ClientNetwork::txMessage(QString msg)
{

}

/*!
 * \brief ClientNetwork::rxAll Read all data and call relevant function to prcess it.
 *
 * Data is avaliable on the in stream (from the server).
 * Read data, validate QJsonObject.
 * Choose next function to call
 */

void ClientNetwork::rxAll()
{
    // Prepare bUnitTest
    for (int i = 20; i <= 29; i++){
        bUnitTest[i] = false;
    }

    // Something was received
    bUnitTest[20] = true;

    in.startTransaction();

    QJsonObject rxObj;
    in >> rxObj;

    if (!in.commitTransaction())
        emit generalError("Client: Datastream read error occured. It is suggested to restart the game.");
        qWarning() << "Client: Datastream error occured.";
        return;

    // Validate the QJsonObject
    // It should contain a Type field, with valid information in the string part.
    if (rxObj.contains("Type") && rxObj["Type"].isString() && rxObj.contains("ID") && rxObj["ID"].isDouble()){
        // QJsonObject received contained the expected data.
        bUnitTest[21] = true;

        // Test if ID number is larger than prevID



    } else {
        // QJsonObject received had errors
        bUnitTest[22] = true;
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qWarning() << "Client: Data received from server has been incorrectly formatted.";

        // TODO: Handel case where data received was incorrect.
        // If not logged in, dissconnect and signal GUI

        // If logged in, request a resend of the data? Or ignaor it, or stop the client.
        // Maybe have a last message detail on server side?
    }

}

void ClientNetwork::internalServerDisconnected()
{

}

/*!
 * \brief ClientNetwork::socketConnected Executed when sucesfully connected to the host (server).
 *
 * Request to see if playerName and password is correct.
 * Create QJsonObject containting the playerName and password.
 * Send the QJsonObject to the server.
 * Make signal and slot conections.
 */

void ClientNetwork::socketConnected()
{
    // Connection was sucessfull
    emit connectionResult(0, "");

    // The first packet received by the server must have an ID of 0.
    idCounter = 0;
    // First packer sent from the client should have an ID of 0 and must be larger than prevID.
    prevID = -1;

    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "CONNECT_REQUEST";
    txObj["Password"] = tempPassword;
    txObj["Alias"] = tempPlayerName;

    // Send the login request to the server
    txAll(txObj);
}

/*!
 * \brief ClientNetwork::socketError Signal the client GUI if an connection error with the server occurs. Abort connection.
 * \param socError QAbstractSocket::SocketError
 */

void ClientNetwork::socketError(QAbstractSocket::SocketError socError)
{
    /*
     * TODO:
     * From Qt documentation (when trying to change the port):
     * When this signal is emitted, the socket may not be ready for a reconnect attempt.
     * In that case, attempts to reconnect should be done from the event loop.
     * For example, use a QTimer::singleShot() with 0 as the timeout.
     */

    // Determine the error
    switch (socError) {
    case QAbstractSocket::HostNotFoundError:
        emit connectionResult(1, "The host was not found. Please check the host IP address and port settings.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        emit connectionResult(1, "The connection was refused by the server. "
                            "Make sure the server is running, "
                            "and check that the host IP address and port settings are correct.");
        break;

    default:
        emit connectionResult(1, "The following error occurred: " + tcpSoc->errorString());
    }

    // TODO: disconnect try to connect again?
    tcpSoc->abort();
}

/*!
 * \brief ClientNetwork::txAll Handel all data that is sent to the server.
 * \param data QJsonObject containing at least the "Type" and "ID" fields.
 */

void ClientNetwork::txAll(QJsonObject data)
{
    qInfo() << "State of the socket: " << tcpSoc->state();
    // Cannot send data if not connected to the server.
    if (tcpSoc->state() != QAbstractSocket::ConnectedState){
        emit generalError("Not connected to the server. Cannot send data to the server.");
        return;
    }

    // Test to see if data that must be sent is valid
    if (not data.contains("Type")){
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
    int tempVal = tcpSoc->write(block);

    qInfo() << "Number of bytes expected to be sent to the server: " << block.size();
    qInfo() << "Number of bytes sent to server: " << tempVal;

    if (tempVal == -1) {
        // An error occured when writing the data block
        emit generalError("An error occured with sending data to the server. It is suggested to restart the game.");
    } else if (tempVal < block.size()) {
        // The block written was too small (did not contain enough bytes).
        emit generalError("An error occured with sending data to the server. It is suggested to restart the game.");
    }
}

void ClientNetwork::rxNotifyBidTurn()
{

}

void ClientNetwork::rxNotifyMoveTurn()
{

}

void ClientNetwork::rxNotifyBidRejected(QJsonObject reasonObj)
{

}

void ClientNetwork::rxNotifyMoveRejected(QJsonObject reasonObj)
{

}

// TODO: handel connection login result

void ClientNetwork::rxLoginResult(QJsonObject resObj)
{

}

void ClientNetwork::rxUpdateGameState(QJsonObject gsObj)
{

}

void ClientNetwork::rxMessage(QJsonObject msgObj)
{

}

void ClientNetwork::rxGameTerminated(QJsonObject reasonObj)
{

}

void ClientNetwork::rxPingReceived()
{

}
