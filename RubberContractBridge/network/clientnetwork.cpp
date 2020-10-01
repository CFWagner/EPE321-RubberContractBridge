#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    // Init internal variables
    gameStarted = false;
    playerName = "";
    keepAlive = nullptr;
    tcpSoc = nullptr;

    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);

    //socketError can use 0 - 4

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
