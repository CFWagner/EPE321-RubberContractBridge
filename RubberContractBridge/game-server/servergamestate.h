#ifndef SERVERGAMESTATE_H
#define SERVERGAMESTATE_H

#include "gamestate.h"
#include "player.h"
#include "playergamestate.h"
#include <QObject>

// Represents the complete state of the game for all players at a given instance in time
class ServerGameState: public QObject, public GameState
{
    Q_OBJECT
public:
    explicit ServerGameState(QObject *parent = nullptr);
    void updateBidState(const Bid &bid);
    void updatePlayState(const Card &card);
    bool isBidValid(const Bid &bid) const;
    bool isCardValid(const Card &card) const;
    const CardSet& getDeck();
    PlayerGameState getPlayerGameState(PlayerPosition player, QVector<Player*> players,
                                       GameEvent gameEvent);
    void startMatch(qint32 maxRubbers);
    // Functions for unit testing purposes
    const QMap<PlayerPosition, CardSet>& getPlayerHands() const;
    void setPlayerHands(const QMap<PlayerPosition, CardSet> &playerHands);
signals:
    void gameEvent(GameEvent gameEvent);
private:
    QMap<PlayerPosition, CardSet> playerHands; // List of cards in each players hand
    QMap<PlayerPosition, CardSet> playerHandsSnapshot; // Snapshot of cards in each players hand at start of deal
    CardSet deck; // Set of 52 unique cards that are dealt at the start of each round
    qint8 passCount; // Number of consecutive passes made during the bidding phase
    qint32 maxRubbers;
    PlayerPosition determineTrickWinner() const;
    static Team getPlayerTeam(PlayerPosition position);
    void nextDeal();
    void nextTrick();
    void nextGame();
    void nextRubber();
};

#endif // SERVERGAMESTATE_H
