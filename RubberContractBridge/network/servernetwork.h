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
    void initServer(QHostAddress ip);
    void stopListening();

private slots:
    void connectClient();
    void validateClient();
    void disconnectClient();

signals:
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

};

#endif // SERVERNETWORK_H
