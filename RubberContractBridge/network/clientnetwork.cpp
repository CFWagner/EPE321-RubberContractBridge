#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);
}

ClientNetwork::~ClientNetwork()
{

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
