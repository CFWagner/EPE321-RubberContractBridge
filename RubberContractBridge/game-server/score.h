#ifndef SCORE_H
#define SCORE_H

#include <QJsonObject>
#include "enumerations/Team.h"
#include "bid.h"
#include "cardset.h"

// Contains the various components of the team scores for a single rubber
class Score
{
public:
    Score();
    Score(quint32 backScore[2]);
    void updateScore(const Bid &contractBid, QMap<PlayerPosition, CardSet> playerHands, quint8 declarerTricksWon);
    const QVector<quint32> getContractPoints(Team team) const;
    quint8 getGamesWon(Team team) const;
    quint32 getBackScore(Team team) const;
    quint32 getOvertricks(Team team) const;
    quint32 getUndertricks(Team team) const;
    quint32 getHonors(Team team) const;
    quint32 getSlamBonuses(Team team) const;
    quint32 getDoubleBonuses(Team team) const;
    quint32 getReDoubleBonuses(Team team) const;
    quint32 getRubberBonuses(Team team) const;
    bool getTeamVulnerable(Team team) const;
    bool isGameWinner() const;
    bool isRubberWinner() const;
    bool isMatchDraw() const;
    void finaliseRubber();
    void nextGame();
    Team getGameWinner() const;
    Team getRubberWinner() const;
    Team getMatchWinner() const;
    quint32 getTotalScore(Team team) const;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const Score& score) const;
private:
    Team getOppositeTeam(Team team) const;
    Team getTeam(PlayerPosition position) const;
    QVector<quint32> contractPoints[2];
    quint32 backScore[2] = {0, 0};
    quint32 overtricks[2] = {0, 0};
    quint32 undertricks[2] = {0, 0};
    quint32 honors[2] = {0, 0};
    quint32 slamBonuses[2] = {0, 0};
    quint32 doubleBonuses[2] = {0, 0};
    quint32 redoubleBonuses[2] = {0, 0};
    quint32 rubberBonuses[2] = {0, 0};
};
#endif // SCORE_H
