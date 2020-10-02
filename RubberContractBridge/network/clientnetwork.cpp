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

    // List of possbile ports to use (may append more ports)
    port.clear();
    port.append(61074);

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

void ClientNetwork::txRequestLogin(QHostAddress serverIP, QString playerName, QString password)
{
    // Connect to the server.

    // Prepare bUnitTest
    for (int i = 5; i <= 9; i++){
        bUnitTest[i] = false;
    }

    // This function started
    bUnitTest[5] = true;

    // Store playerName and password for use after port connected.
    tempPlayerName = playerName;
    tempPassword = password;

    // A static port can be a weak point if the port is already in use.
    // TODO: automatic switching between ports if a port is occupied.
    // TODO: Increament i_port if the current port is occupied.
    int i_port = 0;

    // If connection has already been made, abort it.
    tcpSoc->abort();
    tcpSoc->connectToHost(serverIP, port[i_port]);

    // socketConnected or socketError will be signaled next, depending on connectToHost()'s outcome.

    // This function ended.
    bUnitTest[6] = true;

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

void ClientNetwork::rxAll()
{
    // Data is avaliable on the in stream (from the server).
    // Read data, validate QJsonObject
    // Choose next function to call

    // Prepare bUnitTest
    for (int i = 20; i <= 29; i++){
        bUnitTest[i] = false;
    }

    // Something was received
    bUnitTest[20] = true;

    in.startTransaction();

    QJsonObject rxObj;
    in >> rxObj;

    // Validate the QJsonObject
    // It should contain a Type field, with valid information in the string part.
    if (rxObj.contains("Type") && rxObj["Type"].isString() && rxObj.contains("ID") && rxObj["ID"].isDouble()){
        // QJsonObject received contained the expected data.
        bUnitTest[21] = true;
        // TODO: test ID number, read in communication doc for test?


    } else {
        // QJsonObject received had errors
        bUnitTest[22] = true;

        // TODO: Handel case where data received was incorrect.
        // If not logged in, dissconnect and signal GUI

        // If logged in, request a resend of the data? Or ignaor it, or stop the client.
        // Maybe have a last message detail on server side?
    }

}

void ClientNetwork::internalServerDisconnected()
{

}

void ClientNetwork::socketConnected()
{
    // When sucesfully connected to the host (server).
    // Request to see if playerName and password is correct.
    // Create QJsonObject containting the playerName and password.
    // Send the QJsonObject to the server.
    // Make signal and slot conections.

    // Prepare bUnitTest
    for (int i = 10; i <= 19; i++){
        bUnitTest[i] = false;
    }

    // Connection was sucessfull
    bUnitTest[10] = true;

    // Create transmitting communication data stream
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    // Create QJsonObject
    QJsonObject txObj;
    txObj["Type"] = "CONNECT_REQUEST";
    txObj["ID"] = idCounter++;
    txObj["Password"] = tempPassword;
    txObj["Alias"] = tempPlayerName;

    // Send the login request to the server
    out << txObj;
    int tempVal = tcpSoc->write(block);

    qInfo() << "Number of btes sent to server: " << tempVal;

    if (tempVal == -1) {
        // An error occured when writing the data block
        bUnitTest[11] = true;
    } else if (tempVal <= 19) {
        // The block written was too small (did not contain enough bytes).
        bUnitTest[12] = true;
    } else {
        // If data was send sucessfully
        bUnitTest[13] = true;
    }
}

void ClientNetwork::socketError(QAbstractSocket::SocketError socError)
{
    // Signal the client GUI if an connection error with the server occurs.

    /*
     * TODO:
     * From Qt documentation (when trying to change the port):
     * When this signal is emitted, the socket may not be ready for a reconnect attempt.
     * In that case, attempts to reconnect should be done from the event loop.
     * For example, use a QTimer::singleShot() with 0 as the timeout.
     */

    // Prepare bUnitTest
    for (int i = 0; i <= 4; i++){
        bUnitTest[i] = false;
    }

    // Determine the error
    switch (socError) {
    case QAbstractSocket::RemoteHostClosedError:
        bUnitTest[0] = true;
        break;

    case QAbstractSocket::HostNotFoundError:
        bUnitTest[1] = true;
        emit serverNotFound("The host was not found. Please check the host IP address settings.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        bUnitTest[2] = true;
        emit serverNotFound("The connection was refused by the server. "
                            "Make sure the server is running, "
                            "and check that the host IP address settings are correct.");
        break;

    default:
        bUnitTest[3] = true;
        emit serverNotFound("The following error occurred: " + tcpSoc->errorString());
    }
}

void ClientNetwork::txAll(QJsonObject data)
{

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
