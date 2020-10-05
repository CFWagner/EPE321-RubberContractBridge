#ifndef PLAYERGAMESTATE_H
#define PLAYERGAMESTATE_H

#include "gamestate.h"
#include "enumerations/GameEvent.h"

class PlayerGameState: public GameState
{
public:
    PlayerGameState();
    PlayerGameState(const GameState &gameState, GameEvent gameEvent,
                    QMap<PlayerPosition, QString> playerPositions,
                    CardSet playerHand, CardSet dummyHand);
    GameEvent getEvent();
    CardSet getPlayerHand();
    CardSet getDummyHand();
    QString getPlayerName(PlayerPosition position);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
private:
    GameEvent gameEvent;
    QMap<PlayerPosition, QString> playerPositions;
    CardSet playerHand;
    CardSet dummyHand;
};

#endif // PLAYERGAMESTATE_H
