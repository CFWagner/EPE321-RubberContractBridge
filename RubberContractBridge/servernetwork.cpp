#include "servernetwork.h"

ServerNetwork::ServerNetwork(QObject *parent, QString nameOfAI) : QObject(parent)
{
    ServerNetwork::nameOfAI = nameOfAI;
    tcpServer = nullptr;
}

ServerNetwork::~ServerNetwork()
{

}

QTcpSocket *ServerNetwork::getPlayerSoc(QString playerName) const
{
    return nullptr;
}

void ServerNetwork::setPassword(QString password)
{

}

void ServerNetwork::initServer(QHostAddress ip)
{

}

void ServerNetwork::stopListening()
{

}

void ServerNetwork::connectClient()
{

}

void ServerNetwork::disconnectClient()
{

}

QString ServerNetwork::validateLogin(QString playerName, QString password)
{
    return QString("Temp");
}
