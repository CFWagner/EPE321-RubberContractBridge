#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "player.h"
#include "playergamestate.h"

class ServerGameState: public GameState
{
public:
    ServerGameState();
    ServerGameState(PlayerPosition dealer);
    void nextDeal();
    void nextTrick();
    void updateBidState(const Bid &bid);
    void updatePlayState(const Card &card);
    bool isBidValid(const Bid &bid) const;
    bool isCardValid(const Card &card) const;
    const CardSet& getDeck();
    PlayerGameState getPlayerGameState(PlayerPosition player, QVector<Player*> players,
                                       GameEvent gameEvent);
private:
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet deck;
    qint8 passCount;
    PlayerPosition determineTrickWinner() const;
    static Team getPlayerTeam(PlayerPosition position);
};

#endif // SERVERGAMESTATE_H
