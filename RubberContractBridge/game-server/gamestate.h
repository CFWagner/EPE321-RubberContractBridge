#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "enumerations/GamePhase.h"
#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "bid.h"
#include "cardset.h"
#include "score.h"
#include <QVector>

// Create new game state object for each new match
class GameState
{
public:
    GameState();
    GameState(const GameState &gameState);
    ~GameState();
    GameState& operator = (const GameState &gameState);
    GamePhase getPhase() const;
    const Bid* getCurrentBid() const;
    const Bid* getContractBid() const;
    qint8 getGameNumber() const;
    qint8 getDealNumber() const;
    qint8 getTrickNumber() const;
    const QVector<CardSet> getTricks() const;
    PlayerPosition getPlayerTurn() const;
    PlayerPosition getHandToPlay() const;
    PlayerPosition getDealer() const;
    PlayerPosition getDeclarer() const;
    PlayerPosition getDummy() const;
    bool getTeamVulnerable(Team team) const;
    Score getScore() const;
protected:
    GamePhase phase;
    Bid* currentBid;
    Bid* contractBid;
    qint8 gameNumber;
    qint8 dealNumber;
    qint8 trickNumber;
    QVector<CardSet> tricks;
    PlayerPosition playerTurn;
    PlayerPosition handToPlay;
    PlayerPosition dealer;
    PlayerPosition declarer;
    bool teamVulnerable[2];
    Score score;
};

#endif // GAMESTATE_H
