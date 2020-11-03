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
    qint32 getRubberNumber() const;
    qint8 getGameNumber() const;
    qint8 getDealNumber() const;
    qint8 getTrickNumber() const;
    const QVector<CardSet> getTricks() const;
    PlayerPosition getPlayerTurn() const;
    PlayerPosition getHandToPlay() const;
    PlayerPosition getDealer() const;
    PlayerPosition getDeclarer() const;
    PlayerPosition getDummy() const;
    qint8 getTricksWon(PlayerPosition position) const;
    qint8 getTricksWon(Team team) const;
    bool getTeamVulnerable(Team team) const;
    const Score getScore() const;
    const Card* getLastCardPlayed() const;
protected:
    GamePhase phase;
    // currentBid refers to the most recent valid bid made during the bidding phase
    // nullptr if no bid has been made or phase is CARDPLAY
    Bid* currentBid = nullptr;
    // contractBid refers to the bid accepted as the contract for the game
    // nullptr if phase is BIDDING
    Bid* contractBid = nullptr;
    qint8 rubberNumber;
    qint8 gameNumber;
    qint8 dealNumber; // Zero before first deal
    qint8 trickNumber; // Zero during BIDDING phase
    QVector<CardSet> tricks;
    // Number of tricks won by each player in the current deal
    // Indexed by PlayerPosition enum, NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3
    qint8 tricksWon[4] = {0, 0, 0, 0};
    // PlayerTurn refers to the position of the player who has to select the card to play
    // When it is time to play from the dummy's hand, playerTurn refers to the declarer's position
    PlayerPosition playerTurn;
    // handToPlay refers to the position of the player whose hand the card must be played from
    // When it is time to play from the dummy's hand, handToPlay refers to the dummy's position
    PlayerPosition handToPlay;
    PlayerPosition dealer;
    PlayerPosition declarer;
    Score score;
};
Q_DECLARE_METATYPE(GameState);
#endif // GAMESTATE_H
