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
                    QVector<CardSet> tricks, qint8 tricksWon[4], PlayerPosition playerTurn,
                    PlayerPosition handToPlay, PlayerPosition dealer,
                    PlayerPosition declarer, Score score, GameEvent gameEvent, QMap<PlayerPosition,
                    QString> playerPositions, QMap<PlayerPosition, qint8> playerCardCount,
                    CardSet playerHand, CardSet dummyHand);
    PlayerGameState(const GameState &gameState, GameEvent gameEvent,
                    QMap<PlayerPosition, QString> playerPositions,
                    QMap<PlayerPosition, qint8> playerCardCount,
                    CardSet playerHand, CardSet dummyHand);
    GameEvent getEvent();
    CardSet getPlayerHand();
    CardSet getDummyHand();
    QString getPlayerName(PlayerPosition position);
    qint8 getPlayerCardCount(PlayerPosition position);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const PlayerGameState& playerGameState) const;
    QMap<PlayerPosition, QString> playerPositions; // Map of the postions of the players to the name of the players ine each position;
private:
    GameEvent gameEvent; // Most recent event in the game that can be used to identify which attributes likely changed
    QMap<PlayerPosition, qint8> playerCardCount; // Map of the postions of the players to number of cards each player holds
    CardSet playerHand; // Cards in the hand of the player for which the game state was created
    CardSet dummyHand; // Cards in the dummy's hand. Nullptr if the gamestate is BIDDING
};
Q_DECLARE_METATYPE(PlayerGameState);

#endif // PLAYERGAMESTATE_H
