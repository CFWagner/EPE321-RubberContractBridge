#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "playergamestate.h"

class ServerGameState: public GameState
{
public:
    ServerGameState();
    void initialize();
    void updateBidState(Bid bid);
    void updatePlayState(PlayerPosition player, Card card);
    void updatePhase(GamePhase phase);
    void setDealer(PlayerPosition player);
    void setDeclarer(PlayerPosition player);
    CardSet getDeck();
    PlayerGameState getPlayerGameState(PlayerPosition player);
private:
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet deck;
};

#endif // SERVERGAMESTATE_H
