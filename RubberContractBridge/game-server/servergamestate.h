#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "player.h"
#include "playergamestate.h"

class ServerGameState: public GameState
{
public:
    ServerGameState();
    void nextDeal();
    void nextTrick();
    void updateBidState(Bid* bid);
    void updatePlayState(Card card);
    bool isBidValid(const Bid* bid);
    bool isCardValid(const Card card);
    CardSet getDeck();
    PlayerGameState getPlayerGameState(PlayerPosition player, QVector<Player*> players,
                                       GameEvent gameEvent);
private:
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet deck;
    qint8 passCount;
    PlayerPosition determineTrickWinner();
    static Team getPlayerTeam(PlayerPosition position);
};

#endif // SERVERGAMESTATE_H
