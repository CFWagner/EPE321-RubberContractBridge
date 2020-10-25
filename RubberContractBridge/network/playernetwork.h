#ifndef PLAYERNETWORK_H
#define PLAYERNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QJsonObject>
#include <QHostAddress>

#include "game-server/player.h"
#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "game-server/bid.h"
#include "game-server/card.h"
#include "game-server/playergamestate.h"

class PlayerNetwork : public Player
{
    Q_OBJECT
public:
    explicit PlayerNetwork(QObject *parent = nullptr, QString playerName = QString("Player"), QTcpSocket* clientSoc = nullptr);
    ~PlayerNetwork();

    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState);
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void message(QString source, QString msg);
    void gameTerminated(QString reason);

    // Unit test data
    QVector<bool> getUnitTest() const;

private slots:
    void rxAll();
    void socketError(QAbstractSocket::SocketError socError);
//    void pingClient();

signals:
//    void generalInfo(QString infoMsg); // All information. (Should be displayed to the administrator.)
    void generalError(QString errorMsg); // All errors. (Should be displayed to the administrator.)
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString msg);
    void clientDisconnected();

private:
    void txAll(QJsonObject data);
    void rxBidSelected(QJsonObject bidObj);
    void rxMoveSelected(QJsonObject moveObj);
    void rxMessage(QJsonObject msgObj);
//    void rxPingReturn();
    void internalClientDisconnected(); //Notice the name change between this and the signal's name in the Group design doc.

    QTcpSocket* clientSoc;
    QTimer* keepAlive;
    bool aliveFlag;
    QDataStream in;
    QDataStream out;
    qint64 idCounter;
    qint64 prevID;

    // Unit testing datastructures
    QVector<bool> bUnitTest;
};

#endif // PLAYERNETWORK_H
