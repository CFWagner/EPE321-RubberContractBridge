#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "player.h"
#include "playergamestate.h"

class ServerGameState: public GameState
{
public:
    ServerGameState();
    void updateBidState(Bid* bid);
    void updatePlayState(PlayerPosition player, Card card);
    void updatePhase(GamePhase phase);
    void setDealer(PlayerPosition player);
    void setDeclarer(PlayerPosition player);
    CardSet getDeck();
    PlayerGameState getPlayerGameState(PlayerPosition player, QVector<Player*> players);
private:
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet deck;
    qint8 passCount;
    static bool isBidValid(const Bid* currentBid, const Bid* newBid);
    static Team getPlayerTeam(PlayerPosition position);
};

#endif // SERVERGAMESTATE_H
