#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QJsonObject>
#include <QHostAddress>

class ClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetwork(QObject *parent = nullptr);
    ~ClientNetwork();
    // TODO: Remove this enums and use the correct from the server.
    enum Bid{};
    enum Move{};

private slots:
    void txRequestLogin(QHostAddress serverIP, QString playerName, QString password);
    void txBidSelected(Bid bid);
    void txMoveSelected(Move move);
    void txMessage(QString msg);
    void rxAll();
    void serverDisconnected();

signals:

private:
    void txAll(QJsonObject data);
    void rxNotifyBidTurn();
    void rxNotifyMoveTurn();
    void rxNotifyBidRejected(QJsonObject reasonObj);
    void rxNotifyMoveRejected(QJsonObject reasonObj);
    void rxLoginResult(QJsonObject resObj);
    void rxUpdateGameState(QJsonObject gsObj);
    void rxMessage(QJsonObject msgObj);
    void rxGameTerminated(QJsonObject reasonObj);
    void rxPingReceived();

    QString playerName;
    QTcpSocket* tcpSoc;
    QTimer* keepAlive;
    bool gameStarted;
    QDataStream in;
    QDataStream out;

};

#endif // CLIENTNETWORK_H
