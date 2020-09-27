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
    class Card{};
    class PlayerGameState{};
    enum PlayerPosition{};

    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState);
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void message(QString source, QString msg);
    void gameTerminated(QString reason);
    QString getPlayerName() const;
    PlayerPosition getPosition() const;
    Team getTeam() const;
    void setPosition(PlayerPosition position);
    QString toString() const;

private slots:
    void rxAll();
    void pingClient();

signals:
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString msg);
    void clientDisconnected();

private:
    void txAll(QJsonObject data);
    void rxBidSelected(QJsonObject bidObj);
    void rxMoveSelected(QJsonObject moveObj);
    void rxMessage(QJsonObject msgObj);
    void rxPingReturn();
    void internalClientDisconnected(); //Notice the name change between this and the signal's name in the Group design doc.

    QTcpSocket* clientSoc;
    QTimer* keepAlive;
    bool aliveFlag;
    QDataStream in;
    QDataStream out;
    // playerName and playerPosition is declared in the parent class?
};

#endif // PLAYERNETWORK_H
