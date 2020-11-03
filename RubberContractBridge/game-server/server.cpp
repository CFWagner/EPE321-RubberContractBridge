#include "server.h"
#include "ai/ai.h"
#include "network/playernetwork.h"

// Default constructor
Server::Server(QObject *parent) : QObject(parent)
{
    // Initialise server network
    serverNetwork = new ServerNetwork(parent, "BOT");
    serverLoginWindow = new ServerLogin();
    connect(serverLoginWindow,&ServerLogin::serverPassword,this,&Server::serverPassword);
    connect(serverLoginWindow,&ServerLogin::serverIPAddressPort,this,&Server::serverIPAddressPort);
    connect(serverLoginWindow,&ServerLogin::createLobby,this,&Server::createLobby);
    connect(serverNetwork,&ServerNetwork::connectionResult,serverLoginWindow,&ServerLogin::connectionResult);
    connect(serverNetwork,&ServerNetwork::generalError,serverLoginWindow,&ServerLogin::generalError);
}

// Destructor
Server::~Server()
{
    delete serverNetwork;
    delete gameServer;
    delete loggerWindow;
    delete logger;
}

// Getter for server network
const ServerNetwork& Server::getServerNetwork() const
{
    return *serverNetwork;
}

// Getter for server game state
const ServerGameState& Server::getServerGameState() const
{
    return *gameServer->getState();
}

// Gettter for game server
const GameServer& Server::getGameServer() const
{
    return *gameServer;
}

// Setter for the number of rubbers to be played during the game
void Server::setMaxRubbers(qint32 maxRubbers)
{
    this->maxRubbers = maxRubbers;
}

// Getter for the number of rubbers to be played during the game
qint32 Server::getMaxRubbers() const
{
    return maxRubbers;
}

// Slot for when the players to play the game are selected and the game is started in the server lobby
// Player names are ordered NORTH, SOUTH, EAST, WEST in the playerNames vector
void Server::playersSelected(QVector<QString> playerNames)
{
    // Initialise game server
    delete gameServer;
    gameServer = new GameServer();

    // Instantiate logger window and logger
    loggerWindow = new LoggerWindow();
    logger = new Logger();
    connect(loggerWindow, &LoggerWindow::receivedLog, logger, &Logger::sendLog);
    connect(gameServer, &GameServer::logGenerated, logger, &Logger::log);

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
            player = new PlayerNetwork(this, playerName, playerSocket);
            player->setPosition(position);
        }
        // Connect players to logger
        connect(player, &Player::logGenerated, logger, &Logger::log);
        // Add player to match before match begins
        gameServer->addPlayer(player);
    }

    // Stop listening for incoming connections
    serverNetwork->stopListening();

    // Run the match for specified number of rubbers
    gameServer->executeMatch(maxRubbers);
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

void Server::createLobby()
{
    serverLobby = new ServerLobby();
    connect(serverLobby, &ServerLobby::playersSelected, this,&Server::playersSelected);
    connect(serverNetwork,&ServerNetwork::playerJoined, serverLobby, &ServerLobby::addPlayer);
    connect(serverNetwork,&ServerNetwork::playerDisconnected, serverLobby, &ServerLobby::removePlayer);
    serverLobby->show();
}
