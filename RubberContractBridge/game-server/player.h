#ifndef PLAYER_H
#define PLAYER_H

#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "bid.h"
#include "card.h"
#include "playergamestate.h"
#include <QObject>

// Represents player that partakes in the game of bridge
// Abstract class to enable polymorphism so AI and human players can be treated the same
// way by the game server
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    virtual void notifyBidTurn() = 0;
    virtual void notifyMoveTurn() = 0;
    virtual void updateGameState(PlayerGameState gameState) = 0;
    virtual void notifyBidRejected(QString reason) = 0;
    virtual void notifyMoveRejected(QString reason) = 0;
    virtual void message(QString source, QString message) = 0;
    virtual void gameTerminated(QString reason) = 0;
    QString getPlayerName() const;
    PlayerPosition getPosition() const;
    Team getTeam() const;
    void setPosition(PlayerPosition position);
    void setPlayerName(QString playerName);
protected:
    QString playerName;
    PlayerPosition position;
signals:
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString message);
    void logGenerated(QString context, QString msg);
};

#endif // PLAYER_H
