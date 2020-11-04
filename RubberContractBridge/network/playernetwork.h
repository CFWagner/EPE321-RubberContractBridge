#ifndef PLAYERNETWORK_H
#define PLAYERNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
//#include <QTimer>
#include <QDateTime>
#include <QJsonObject>
#include <QHostAddress>
#include <QCoreApplication>

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

    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState); // After the game has been started, this should be the first function called.
    // By calling this function, the client is informed that it has been selected to be part of a game and that the game has started.
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void message(QString source, QString msg);
    void gameTerminated(QString reason);
    // Reason will probably be displaye to the end user.

private slots:
    void rxAll();
    void socketError(QAbstractSocket::SocketError socError);

signals:
    void generalError(QString errorMsg); // All errors. (Should be displayed to the administrator.)
    // No generalError given when client unexpectedly disconnects, rather clientDisconnected is emmited.
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString msg);
    void clientDisconnected();
    // This will be emited when the client disconnects (including when the client is destructed.)
    // This will probably be emitted after gameTerminated() was send. (Untested.)

private:
    void txAll(QJsonObject data);
    void rxBidSelected(QJsonObject bidObj);
    void rxMoveSelected(QJsonObject moveObj);
    void rxMessage(QJsonObject msgObj);
    void internalClientDisconnected(); //Notice the name change between this and the signal's name in the Group design doc.

    QTcpSocket* clientSoc;
    QDataStream in;
    qint64 idCounter;
    qint64 prevID;
    bool gameTerminatedOnce;
};

#endif // PLAYERNETWORK_H
