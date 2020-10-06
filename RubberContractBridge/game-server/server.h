#ifndef SERVER_H
#define SERVER_H

#include "gameserver.h"
#include <QHostAddress>
#include <QObject>

// Highest level class on the server side
// Purpose is to connect server interface, game server and server networking components
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
public slots:
    void gameEvent(GameEvent event);
    void playersSelected(QVector<QString> playerNames);
    void playerDisconnected();
    void serverPassword(QString passwordSent);
    void serverIPAddress(QHostAddress addressSent);
private:
    GameServer gameServer;
};

#endif // SERVER_H
