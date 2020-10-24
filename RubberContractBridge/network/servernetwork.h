#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>
#include <QDataStream>
Q_DECLARE_METATYPE(QHostAddress); // To allow to test signals with this argument type

// This might not be needed but is included in the Fortune Server example.
//QT_BEGIN_NAMESPACE
//class QTcpSocket;
//class QTcpServer;
//QT_END_NAMESPACE

class ServerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ServerNetwork(QObject *parent = nullptr, QString nameOfAI = QString("AI"));
    ~ServerNetwork();

    QTcpSocket* getPlayerSoc(QString playerName);
    void setPassword(QString password);
    void initServer(QHostAddress ip, quint16 port);
    void stopListening();

    // Unit test data
    QVector<bool> getUnitTest();

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
    // GUI is responsible for creating the messages regarding connection status. (General Info and Warning signals will not be used for this.)

//    void generalInfo(QString infoMsg);
    // All information, such as the port it connected to. (Should be displayed to the administrator.)

    void generalError(QString errorMsg);
    // All errors. (Should be displayed to the administrator.)

    void playerJoined(QString playerName);
    void playerDisconnected(QString playerName); // Disconnect from this signal before deleting the serverNetwork class.
    // This is to avoid many unused clients from signaling you when they are deleted.

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

    // Unit testing datastructures
    QVector<bool> bUnitTest;

};

#endif // SERVERNETWORK_H
