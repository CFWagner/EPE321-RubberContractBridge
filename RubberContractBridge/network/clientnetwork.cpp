#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    // Init internal variables
    gameStarted = false;
    playerName = "";
    keepAlive = nullptr;
    tcpSoc = nullptr;

    // List of possbile ports to use (may append more ports)
    port.clear();
    port.append(61074);

    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);

    //socketError can use 0 - 4
    //txRequestLogin can use 10 - 19

    // Prepare the tcpSoc and datastream
    tcpSoc = new QTcpSocket(this);

    in.setDevice(tcpSoc);
    in.setVersion(QDataStream::Qt_5_10);

    // Create connections
    // All reception
    connect(tcpSoc, &QIODevice::readyRead, this, &ClientNetwork::rxAll);
    // Connection errors
    connect(tcpSoc, &QAbstractSocket::errorOccurred, this, &ClientNetwork::socketError);
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
    // Make signal and slot conections.
    // Create QJsonObject containting the playerName and password.
    // Send the QJsonObject to the server.

    // Prepare bUnitTest
    for (int i = 10; i <= 19; i++){
        bUnitTest[i] = false;
    }

    // A static port can be a weak point if the port is already in use.
    // TODO: automatic switching between ports if a port is occupied.
    // TODO: Increament i_port if the current port is occupied.
    int i_port = 0;

    tcpSoc->abort();
    tcpSoc->connectToHost(serverIP, port[i_port]);

    // If sucesfully connected to the host (server)
    bUnitTest[10] = true;


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

}

void ClientNetwork::internalServerDisconnected()
{

}

void ClientNetwork::socketError(QAbstractSocket::SocketError socError)
{
    // Signal the client GUI if an connection error with the server occurs.

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
