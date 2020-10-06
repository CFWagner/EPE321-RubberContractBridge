#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "player.h"
#include "playergamestate.h"

// Represents the complete state of the game for all players at a given instance in time
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
    QMap<PlayerPosition, CardSet> playerHands; // List of cards in each players hand
    CardSet deck; // Set of 52 unique cards that are dealt at the start of each round
    qint8 passCount; // Number of consecutive passes made during the bidding phase
    PlayerPosition determineTrickWinner() const;
    static Team getPlayerTeam(PlayerPosition position);
};

#endif // SERVERGAMESTATE_H
