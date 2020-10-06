#ifndef PLAYERGAMESTATE_H
#define PLAYERGAMESTATE_H

#include "gamestate.h"
#include "enumerations/GameEvent.h"

// Represents the state of the game at a given instance in time
// Game state is tailored for a specific player so they can only
// access game state information that is allowed for them
class PlayerGameState: public GameState
{
public:
    PlayerGameState();
    PlayerGameState(GamePhase phase, const Bid* currentBid, const Bid* contractBid,
                    qint8 gameNumber,qint8 dealNumber, qint8 trickNumber,
                    QVector<CardSet> tricks, PlayerPosition playerTurn,
                    PlayerPosition handToPlay, PlayerPosition dealer,
                    PlayerPosition declarer, bool teamVulnerable[2],
                    Score score, GameEvent gameEvent, QMap<PlayerPosition, QString> playerPositions,
                    CardSet playerHand, CardSet dummyHand);
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
    GameEvent gameEvent; // Most recent event in the game that can be used to identify which attributes likely changed
    QMap<PlayerPosition, QString> playerPositions; // Map of the postions of the players to the name of the players ine each position
    CardSet playerHand; // Cards in the hand of the player for which the game state was created
    CardSet dummyHand; // Cards in the dummy's hand. Nullptr if the gamestate is BIDDING
};

#endif // PLAYERGAMESTATE_H
