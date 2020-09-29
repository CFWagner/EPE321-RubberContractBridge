#include "clientnetwork.h"

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{

}

ClientNetwork::~ClientNetwork()
{

}

void ClientNetwork::txRequestLogin(QHostAddress serverIP, QString playerName, QString password)
{

}

void ClientNetwork::txBidSelected(ClientNetwork::Bid bid)
{

}

void ClientNetwork::txMoveSelected(ClientNetwork::Move move)
{

}

void ClientNetwork::txMessage(QString msg)
{

}

void ClientNetwork::rxAll()
{

}

void ClientNetwork::serverDisconnected()
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
