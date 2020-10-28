#include "server.h"
#include "ai/ai.h"
#include "network/playernetwork.h"

// Default constructor
Server::Server(QObject *parent) : QObject(parent)
{
    // Initialise server network
    serverNetwork = new ServerNetwork(parent, "BOT");

    // Initialise game server
    gameServer = new GameServer();

    // Initialise signal and slot connections
}

Server::~Server()
{
    delete serverNetwork;
    delete gameServer;
}

// Getter for server network
const ServerNetwork& Server::getServerNetwork() const
{
    return *serverNetwork;
}

// Slot for when an event occurs in the game server
void Server::gameEvent(GameEvent event)
{

}


// Slot for when the players to play the game are selected and the game is started in the server lobby
// Player names are ordered NORTH, SOUTH, EAST, WEST in the playerNames vector
void Server::playersSelected(QVector<QString> playerNames)
{
    // Create players and add to game server
    for(qint8 i = 0; i < playerNames.length(); ++ i){
        // Get player name and position
        QString playerName = playerNames.value(i);
        PlayerPosition position;
        switch (i) {
        case 0:
            position = NORTH;
            break;
        case 1:
            position = SOUTH;
            break;
        case 2:
            position = EAST;
            break;
        default:
            position = WEST;
            break;
        }

        // Create players
        Player* player;
        // Create AI player
        if(playerName.contains("BOT")){
            player = new AI();
            player->setPlayerName(playerName);
            player->setPosition(position);
        }
        // Create human player
        else{
            QTcpSocket* playerSocket = serverNetwork->getPlayerSoc(playerName);
            player = new PlayerNetwork(nullptr, playerName, playerSocket);
            player->setPosition(position);
        }

        gameServer->addPlayer(player);
    }

    //
    gameServer->executeMatch(5);
}

// Slot for when a player disconnects from the server
void Server::playerDisconnected()
{

}

// Slot for when the server password is selected in the server login menu
void Server::serverPassword(QString passwordSent)
{
    serverNetwork->setPassword(passwordSent);
}

// Slot for when the server IP address and port is selected in the server login menu
void Server::serverIPAddressPort(QHostAddress addressSent, quint16 portSent)
{
    serverNetwork->initServer(addressSent, portSent);
}
