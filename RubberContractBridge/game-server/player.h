#ifndef PLAYER_H
#define PLAYER_H

#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "bid.h"
#include "card.h"
#include "playergamestate.h"
#include <QObject>

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
protected:
    QString playerName;
    PlayerPosition position;
signals:
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString message);
};

#endif // PLAYER_H
