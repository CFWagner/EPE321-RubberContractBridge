#ifndef PLAYERNETWORK_H
#define PLAYERNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QJsonObject>
#include <QHostAddress>


class PlayerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit PlayerNetwork(QObject *parent = nullptr, QString playerName = QString("Player"), QTcpSocket* clientSoc = nullptr);
    ~PlayerNetwork();
    // TODO: Remove this enums and use the correct from the server.
    enum Bid{};
    enum Move{};
    enum Team{};
    class PlayerGameState{};
    enum PlayerPosition{};

    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState);
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void message(QString source, QString msg);
    void gameTerminated(QString reason);
    QString getPlayerName();
    PlayerPosition getPosition();
    Team getTeam();
    void setPosition(PlayerPosition position);
    QString toString();
private slots:

signals:

private:
    QTcpSocket* clientSoc;
    QTimer* keepAlive;
    bool aliveFlag;
    QDataStream in;
    QDataStream out;


};

#endif // PLAYERNETWORK_H
