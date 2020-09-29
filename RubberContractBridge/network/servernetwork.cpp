#include "servernetwork.h"

ServerNetwork::ServerNetwork(QObject *parent, QString nameOfAI) : QObject(parent)
{
    // Init all variables
    this->nameOfAI = nameOfAI;
    tcpServer = nullptr;

    // Set a default password, this should be changed by the server.
    password = "12340000";
    playerNames.clear();
    clientSoc.clear();
    clientSocTemp.clear();
    tcpServer = nullptr;
}

ServerNetwork::~ServerNetwork()
{
    // Stop the server
    if (tcpServer != nullptr) {
        disconnect(tcpServer, &QTcpServer::newConnection, 0, 0);
        tcpServer->close();
    }
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
    // The IP address can only be set once after the program has started.
    qint16 port = 61074;

    // Check if the server has been initialized.
    if (tcpServer != nullptr){
        qWarning() << "The IP address can only be set once. Nothing was changed.";
    } else {
        // Test if ip address is valid.
        // If not valid, use local host, since it will be run on one machine.
        // Print this descision to qWarning.

        // Find all valid ipAdresses.
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        if ((ip.toString().isEmpty() == true) || (ipAddressesList.contains(ip) == false)) {
            qWarning() << "The selected IP address (" << ip.toString() << ") for the server is not valid. Localhost will be used instead.";
            ip = QHostAddress::LocalHost;
        }

        qInfo() << "Final IP used for the server: " << ip.toString();

        // Disconnect the client
        //    if (clientConnection != nullptr){
        //        disconnect(clientConnection, &QIODevice::readyRead,0,0);
        //        clientConnection->disconnectFromHost();
        //        clientConnection = nullptr;
        //    }

        //    disconnect(tcpServer, &QTcpServer::newConnection, 0, 0);


        tcpServer = new QTcpServer(this);

        if (!tcpServer->listen(ip, port)) {
            qCritical() << "DRCB - ServerNetwork" << "Unable to start the server: " << tcpServer->errorString();
            return;
        }

        connect(tcpServer, &QTcpServer::newConnection, this, &ServerNetwork::connectClient);

        qInfo() << "The server is listening for clients on " << ip.toString() << " with port: " << tcpServer->serverPort();
    }

}

void ServerNetwork::stopListening()
{
    // Stop listen for new client connections.

}

void ServerNetwork::connectClient()
{
    // Accept new client connections.
    // Add client to clientSocTemp.
    // Make signal slot connections.


}

void ServerNetwork::validateClient()
{
    // Validate the password and username.
    // If valid, add username and client socket.
    // Signal the GUI that a client has logged in.
    // If not valid, disconnect the client.

    // Get the sender's QTcpSocket
    QObject* obj = sender();
    QTcpSocket* tempSocket = qobject_cast<QTcpSocket*>(obj);

    // Remove clientSock from the clientSocTemp.
    clientSocTemp.removeAll(tempSocket);

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
