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
    const ServerGameState& getServerGameState() const;
    const GameServer& getGameServer() const;
    void setMaxRubbers(qint32 maxRubbers);
    qint32 getMaxRubbers() const;
public slots:
    void playersSelected(QVector<QString> playerNames);
    void serverPassword(QString passwordSent);
    void serverIPAddressPort(QHostAddress addressSent,quint16 portSent);
private:
    qint32 maxRubbers;
    ServerNetwork* serverNetwork = nullptr;
    GameServer* gameServer = nullptr;
};

#endif // SERVER_H
