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

    // Init unit test
    bUnitTest.clear();
    bUnitTest.fill(false,40);

    //getPlayerSoc can use 0 - 9
    //initServer can use 10 - 19
    //connectClient can use 20 - 29
    //validateClient can use 30 - 39
}

ServerNetwork::~ServerNetwork()
{
    qInfo() << "ServerNetwork destructed";
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

    // Prepare bUnitTest
    for (int i = 10; i <= 19; i++){
        bUnitTest[i] = false;
    }

    // Check if the server has been initialized.
    if (tcpServer != nullptr){
        qWarning() << "The IP address can only be set once. Nothing was changed.";
        bUnitTest[10] = true;
    } else {
        // Test if ip address is valid.
        // If not valid, use local host, since it will be run on one machine.
        // Print this descision to qWarning.

        // Find all valid ipAdresses.
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        if ((ip.toString().isEmpty() == true) || (ipAddressesList.contains(ip) == false)) {
            qWarning() << "The selected IP address (" << ip.toString() << ") for the server is not valid. Localhost will be used instead.";
            ip = QHostAddress::LocalHost;
            bUnitTest[11] = true;
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
            bUnitTest[12] = true;
            return;
        }

        connect(tcpServer, &QTcpServer::newConnection, this, &ServerNetwork::connectClient);

        qInfo() << "The server is listening for clients on " << ip.toString() << " with port: " << tcpServer->serverPort();
        bUnitTest[13] = true;
    }

}

void ServerNetwork::stopListening()
{
    // Stop listen for new client connections.

}

QVector<bool> ServerNetwork::getUnitTest() const
{
    return bUnitTest;
}

void ServerNetwork::connectClient()
{
    // Accept new client connections.
    // Add client to clientSocTemp.
    // Make signal slot connections.

    // Prepare bUnitTest
    for (int i = 20; i <= 29; i++){
        bUnitTest[i] = false;
    }

    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();


    if (!clientConnection) {
        qWarning() << "Got invalid pending connection! Ignoring the connection.";
        bUnitTest[20] = true;
        return;
    }

    connect(clientConnection, &QIODevice::readyRead,this, &ServerNetwork::validateClient);
    connect(clientConnection, &QAbstractSocket::disconnected,this, &ServerNetwork::disconnectClient);
    connect(clientConnection, &QAbstractSocket::disconnected,clientConnection, &QObject::deleteLater);

    // Add to temp list.
    clientSocTemp.append(clientConnection);
}

void ServerNetwork::validateClient()
{
    // Validate the password and username.
    // If valid, add username and client socket.
    // Signal the GUI that a client has logged in.
    // If not valid, disconnect the client.

    // Prepare bUnitTest
    for (int i = 30; i <= 39; i++){
        bUnitTest[i] = false;
    }

    // Get the sender's QTcpSocket
    QObject* obj = sender();
    QTcpSocket* tempSocket = qobject_cast<QTcpSocket*>(obj);

    // Remove clientSock from the clientSocTemp.
    int numRemoved = clientSocTemp.removeAll(tempSocket);

    // Check if tempSocket is the same as previously saved.
    if (numRemoved == 0){
        bUnitTest[30] = true;
    }

    // Check for unexpected sockets
    if (numRemoved > 1) {
        bUnitTest[31] = true;
    }

    // Read data from the socket
    in.setDevice(tempSocket);
    in.setVersion(QDataStream::Qt_5_10);
    // Read the data
    in.startTransaction();
    QJsonObject inputFromClient;
    in >> inputFromClient;
    if (!in.commitTransaction()) {
        // If read error occured, this should not happen.
        // If this occurs, the connection to the client must be terminated.
        bUnitTest[32] = true;
        tempSocket->disconnectFromHost();
        return;
    }

    // Validate and read the QJsonObject.
    // Read the data. (Password and username.)
    QString validateRes = "";


    // TODO: Change this to test the actual username and password.
    validateRes = validateLogin("","");
}

void ServerNetwork::validateClient()
{
    // Validate the password and username.
    // If valid, add username and client socket.
    // Signal the GUI that a client has logged in.
    // If not valid, disconnect the client.

    // Prepare bUnitTest
    for (int i = 30; i <= 39; i++){
        bUnitTest[i] = false;
    }

    // Get the sender's QTcpSocket
    QObject* obj = sender();
    QTcpSocket* tempSocket = qobject_cast<QTcpSocket*>(obj);

    // Remove clientSock from the clientSocTemp.
    int numRemoved = clientSocTemp.removeAll(tempSocket);

    // Check if tempSocket is the same as previously saved.
    if (numRemoved == 0){
        bUnitTest[30] = true;
    }

    // Check for unexpected sockets
    if (numRemoved > 1) {
        bUnitTest[31] = true;
    }

    // Read data from the socket
    in.setDevice(tempSocket);
    in.setVersion(QDataStream::Qt_5_10);
    // Read the data
    in.startTransaction();
    QJsonObject inputFromClient;
    in >> inputFromClient;
    if (!in.commitTransaction()) {
        // If read error occured, this should not happen.
        // If this occurs, the connection to the client must be terminated.
        bUnitTest[32] = true;
        tempSocket->disconnectFromHost();
        return;
    }

    // Validate and read the QJsonObject.
    // Read the data. (Password and username.)
    QString validateRes = "";


    // TODO: Change this to test the actual username and password.
    validateRes = validateLogin("","");
}

void ServerNetwork::validateClient()
{
    // Validate the password and username.
    // If valid, add username and client socket.
    // Signal the GUI that a client has logged in.
    // If not valid, disconnect the client.

    // Prepare bUnitTest
    for (int i = 30; i <= 39; i++){
        bUnitTest[i] = false;
    }

    // Get the sender's QTcpSocket
    QObject* obj = sender();
    QTcpSocket* tempSocket = qobject_cast<QTcpSocket*>(obj);

    // Remove clientSock from the clientSocTemp.
    int numRemoved = clientSocTemp.removeAll(tempSocket);

    // Check if tempSocket is the same as previously saved.
    if (numRemoved == 0){
        bUnitTest[30] = true;
    }

    // Check for unexpected sockets
    if (numRemoved > 1) {
        bUnitTest[31] = true;
    }

    // Read data from the socket
    in.setDevice(tempSocket);
    in.setVersion(QDataStream::Qt_5_10);
    // Read the data
    in.startTransaction();
    QJsonObject inputFromClient;
    in >> inputFromClient;
    if (!in.commitTransaction()) {
        // If read error occured, this should not happen.
        // If this occurs, the connection to the client must be terminated.
        bUnitTest[32] = true;
        tempSocket->disconnectFromHost();
        return;
    }

    // Validate and read the QJsonObject.
    // Read the data. (Password and username.)
    QString validateRes = "";


    // TODO: Change this to test the actual username and password.
    validateRes = validateLogin("","");
}

void ServerNetwork::disconnectClient()
{
    // When a client disconnects, check if the client logged in.
    // If logged in, remove username and client socket.
    // Signal the GUI to also remove the client.

    qInfo() << "Socket disconnected";

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
