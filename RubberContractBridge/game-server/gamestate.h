#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "enumerations/GamePhase.h"
#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "bid.h"
#include "cardset.h"
#include "score.h"
#include <QVector>

class GameState
{
public:
    GameState();
    ~GameState();
    GamePhase getPhase();
    const Bid* getCurrentBid();
    const Bid* getContractBid();
    qint8 getGameNumber();
    qint8 getDealNumber();
    qint8 getTrickNumber();
    const QVector<CardSet> getTricks();
    PlayerPosition getPlayerTurn();
    PlayerPosition getHandToPlay();
    PlayerPosition getDealer();
    PlayerPosition getDeclarer();
    PlayerPosition getDummy();
    bool getTeamVulnerable(Team team);
    Score getScore();
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
