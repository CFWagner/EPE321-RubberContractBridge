#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>
#include <QDataStream>

#ifndef DECLARE_METATYPE_QHostAddress
#define DECLARE_METATYPE_QHostAddress
Q_DECLARE_METATYPE(QHostAddress); // To allow to test signals with this argument type
#endif // DECLARE_METATYPE_QHostAddress

class ServerNetwork : public QObject
{
    Q_OBJECT
public:
    // The server should not be destructed before the game has finished.
    explicit ServerNetwork(QObject *parent = nullptr, QString nameOfAI = QString("AI"));
    ~ServerNetwork();
    void forceError(); // Only used in unit tests. Will emit a generalError signal.

    QTcpSocket* getPlayerSoc(QString playerName);
    void setPassword(QString password); // Call before calling initServer.
    void initServer(QHostAddress ip, quint16 port);
    // Once connected to a port, the port is only relesed after the application has been terminated.
    void stopListening(); // Call this just before the game starts and after getting all the Player sockets.

private slots:
    void connectClient();
    void validateClient();
    void disconnectClient();

signals:
    void connectionResult(int status, QHostAddress ip, quint16 port, QString errorMsg);
    // status = 0 :connection was successful
    // status = 1 :connection was not successful, since the IP address is invalid (no info regarding port number validness can be given).
    // status = 2 :connection was not successful, IP address is valid and port number is not valid. (See errorMsg description below.)
    // status = 3 :already connected, old connection was kept. ("The server can only be initialized once. Nothing was changed.")
    // ip and port is the ip and port given as arguments to the initServer function.
    // errorMsg is empty except when status = 2, then the actual error will be displayed. (It might not be a port error,
    // but that is the most likely error to have occured. If status = 2 and errorMsg = "The bound address is already in use", then it is
    // definitively the port that is already in use.)
    // GUI is responsible for creating the messages regarding connection status. (generalError signals will not be used for this.)

    void generalError(QString errorMsg);
    // All errors. (Should be displayed to the administrator.)
    // No generalError emited when a client unexpectedly disconnects.

    void playerJoined(QString playerName);
    void playerDisconnected(QString playerName);
    // After stopListening called, playerDisconnected will not be emited again.

private:
    QString validateLogin(QString playerName, QString password);

    QString password;
    QString nameOfAI;
    QVector<QString> playerNames;
    QVector<QTcpSocket*> clientSoc;
    QVector<QTcpSocket*> clientSocTemp;
    QTcpServer* tcpServer;
    QDataStream in;
    bool bAllowNewClientConnection;
};

#endif // SERVERNETWORK_H
