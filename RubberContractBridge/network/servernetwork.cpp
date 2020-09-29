#include "servernetwork.h"

ServerNetwork::ServerNetwork(QObject *parent, QString nameOfAI) : QObject(parent)
{
    // Init all variables
    this->nameOfAI = nameOfAI;
    tcpServer = nullptr;

    // Set a default password, this should be changed by the server/
    password = "12340000";
    playerNames.clear();
    clientSoc.clear();
    tcpServer = nullptr;
}

ServerNetwork::~ServerNetwork()
{

}

QTcpSocket *ServerNetwork::getPlayerSoc(QString playerName) const
{
    // Return the socket that corresponds to the playerName.
    // Throw an error if playerName can not be found and return nullptr.
    return nullptr;
}

void ServerNetwork::setPassword(QString password)
{
    // Password strength and validness should be checked in the serverGUI.
    this->password = password;
}

void ServerNetwork::initServer(QHostAddress ip)
{
    // Open a port on the given ip address.
    // Use port 61074.
    // Start listening for clients that want to connect.


}

void ServerNetwork::stopListening()
{
    // Stop listen for new client connections.

}

void ServerNetwork::connectClient()
{
    // Accept new client connections.
    // Validate the password and username.
    // If valid, add username and client socket.
    // Signal the GUI that a client has logged in.
    // If not valid, disconnect the client.

}

void ServerNetwork::disconnectClient()
{
    // When a client disconnects, check if the client logged in.
    // If logged in, remove username and client socket.
    // Signal the GUI to also remove the client.

}

QString ServerNetwork::validateLogin(QString playerName, QString password)
{
    // Validate the password and playerName.
    // If both are valid, return an empty string.
    // Else return the reason for faliure. This message will be displayed to the user.
    // Check if password match.
    // Check if username is empty.
    // Check if username is longer than 15 chars.
    // Check if username correspons to an AI player.
    // Check if the username has been used before.

    return QString("Temp");
}
