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
    // <open> can use 10 - 19
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

void ServerNetwork::initServer(QHostAddress ip, qint16 port)
{
    // Open a port on the given ip address.
    // Use port 61074.
    // Start listening for clients that want to connect.
    // The IP address can only be set once after the program has started.

    // Prepare bUnitTest
    for (int i = 10; i <= 19; i++){
        bUnitTest[i] = false;
    }

    // Check if the server has been initialized.
    if (tcpServer != nullptr){
        emit connectionResult(3, ip, port, "");
        return;

    }

    // Test if ip address is valid.

    // Find all valid ipAdresses.
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    if ((ip.toString().isEmpty() == true) || (ipAddressesList.contains(ip) == false)) {
        emit connectionResult(1, ip, port, "");
        return;
    }

    // Disconnect the client
    //    if (clientConnection != nullptr){
    //        disconnect(clientConnection, &QIODevice::readyRead,0,0);
    //        clientConnection->disconnectFromHost();
    //        clientConnection = nullptr;
    //    }

    //    disconnect(tcpServer, &QTcpServer::newConnection, 0, 0);


    tcpServer = new QTcpServer(this);

    if (!tcpServer->listen(ip, port)) {
        emit connectionResult(2, ip, port, tcpServer->errorString());

        // Set tcpServer to null, so that a new QTcpServer can be constructed on the second try.
        tcpServer->deleteLater();
        tcpServer = nullptr;

        return;
    }

    // The connection was successfull.
    connect(tcpServer, &QTcpServer::newConnection, this, &ServerNetwork::connectClient);

    qInfo() << "The server is listening for clients on " << ip.toString() << " with port: " << tcpServer->serverPort();
    emit connectionResult(0,ip,port,"");

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

    QTcpSocket* clientConnection = tcpServer->nextPendingConnection();


    if (!clientConnection) {
        emit generalError("Got invalid pending connection! Ignoring the connection.");
        return;
    }

    connect(clientConnection, &QIODevice::readyRead,this, &ServerNetwork::validateClient);
    connect(clientConnection, &QAbstractSocket::disconnected,this, &ServerNetwork::disconnectClient);
    connect(clientConnection, &QAbstractSocket::disconnected,clientConnection, &QObject::deleteLater);

    // Add to temp list.
    clientSocTemp.append(clientConnection);
}

/*!
 * Validate the password and username.
 * If valid, add username and client socket.
 * Signal the GUI that a client has logged in.
 * If invalid, disconnect the client.
 */

void ServerNetwork::validateClient()
{
    // If avlidateRes is empty at the end of this function,
    // no errors occured and the login request has been accepted.
    QString validateRes = "";

    // Get the sender's QTcpSocket
    QObject* obj = sender();
    QTcpSocket* tempSocket = qobject_cast<QTcpSocket*>(obj);

    // Remove clientSock from the clientSocTemp.
    int numRemoved = clientSocTemp.removeAll(tempSocket);

    // Check if tempSocket is the same as previously saved.
    if (numRemoved == 0){
        emit generalError("An unexpected client connected. Client forcefully removed.");
        tempSocket->abort();
        return;
    }

    // Check for unexpected sockets
    if (numRemoved > 1) {
        emit generalError("Duplicate clients existed and was removed. The error will be ignored.");
    }

    // Read data from the socket
    in.setDevice(tempSocket);
    in.setVersion(QDataStream::Qt_5_10);

    in.startTransaction();

    QJsonObject rxObj;
    in >> rxObj;

    if (!in.commitTransaction()){
        emit generalError("Datastream read error occured. It is suggested to restart the game.");
        qWarning() << "Datastream error occured.";
        return;
    }

    // Validate the QJsonObject
    // It should contain a Type field, with valid information in the string part.
    if (rxObj.contains("Type") && rxObj["Type"].isString() && rxObj.contains("ID") && rxObj["ID"].isDouble()){
        // QJsonObject received contained the expected data.
        // Test if ID number is larger than prevID
        if (rxObj["ID"].toInt() <= 0) {
            emit generalError("Outdated data was received. The data will be ignored.");
            validateRes.append("The login request was too old and thus not accepted.");
        }

    } else {
        // QJsonObject received had errors
        emit generalError("Data received from server has been incorrectly formatted. It is suggested to restart the game.");
        qWarning() << "Data received from client has been incorrectly formatted.";
        validateRes.append("The login request was not formatted correctly.");
    }

    // Read the data
    in.startTransaction();
    QJsonObject inputFromClient;
    in >> inputFromClient;
    if (!in.commitTransaction()) {
        // Read error occured: this should not happen.
        // If this occurs, the connection to the client must be terminated.
        bUnitTest[32] = true;
        tempSocket->disconnectFromHost();
        return;
    }

    // Validate and read the QJsonObject.
    // Read the data. (Password and username.)
    // ID should be 0
//    QString validateRes = "";


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
