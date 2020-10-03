#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>
#include <QDataStream>

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

    QTcpSocket* getPlayerSoc(QString playerName) const;
    void setPassword(QString password);
    void initServer(QHostAddress ip, qint16 port);
    void stopListening();

    // Unit test data
    QVector<bool> getUnitTest() const;

private slots:
    void connectClient();
    void validateClient();
    void disconnectClient();

signals:
    void connectionResult(int status, QHostAddress ip, qint16 port);
    // status = 0 :connection was successful
    // status = 1 :connection was not successful, since the IP address is invalid (no info regarding port number validness can be given).
    // status = 2 :connection was not successful, IP address is valid and port number is not valid.
    // GUI is responsible for creating the messages regarding connection status. (genearl Info and warning signals will not be used for this.)

    void generalInfo(QString infoMsg); // All information, such as the port it connected to. (Should be displayed to the administrator.)
    void generalError(QString errorMsg); // All errors. (Should be displayed to the administrator.)
    void playerJoined(QString playerName);
    void playerDisconnected(QString playerName);

private:
    QString validateLogin(QString playerName, QString password);

    QString password;
    QString nameOfAI;
    QVector<QString> playerNames;
    QVector<QTcpSocket*> clientSoc;
    QVector<QTcpSocket*> clientSocTemp;
    QTcpServer* tcpServer;
    QDataStream in;
    QDataStream out;
    QVector<qint16> port;

    // Unit testing datastructures
    QVector<bool> bUnitTest;

};

#endif // SERVERNETWORK_H
