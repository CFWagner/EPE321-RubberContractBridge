#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

void Server::gameEvent(GameEvent event)
{

}

void Server::playersSelected(QVector<QString> playerNames)
{

}

void Server::playerDisconnected()
{

}

void Server::serverPassword(QString passwordSent)
{
    qDebug () << passwordSent;
}

void Server::serverIPAddressPort(QHostAddress addressSent,quint16 portSent)
{
    qDebug () << addressSent;
    qDebug () << portSent;
}
