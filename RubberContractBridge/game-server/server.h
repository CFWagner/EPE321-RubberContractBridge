#ifndef SERVER_H
#define SERVER_H

#include "gameserver.h"
#include "network/servernetwork.h"
#include <QHostAddress>
#include <QObject>

// Highest level class on the server side
// Purpose is to connect server interface, game server and server networking components
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
    const ServerNetwork& getServerNetwork() const;
public slots:
    void gameEvent(GameEvent event);
    void playersSelected(QVector<QString> playerNames);
    void playerDisconnected();
    void serverPassword(QString passwordSent);
    void serverIPAddressPort(QHostAddress addressSent,quint16 portSent);
private:
    ServerNetwork* serverNetwork;
    GameServer* gameServer;
};

#endif // SERVER_H
