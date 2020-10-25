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
    void updateScore(const Bid &contractBid, QMap<PlayerPosition, CardSet> playerHands, quint8 defenderTricksWon);
    const QVector<quint32> getContractPoints(Team team) const;
    quint32 getBackScore(Team team) const;
    quint32 getOvertricks(Team team) const;
    quint32 getUndertricks(Team team) const;
    quint32 getHonors(Team team) const;
    quint32 getSlamBonuses(Team team) const;
    bool getTeamVulnerable(Team team) const;
    void setTeamVulnerable(Team team);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const Score& score) const;
private:
    QVector<quint32> contractPoints[2];
    quint32 backScore[2] = {0, 0};
    quint32 overtricks[2] = {0, 0};
    quint32 undertricks[2] = {0, 0};
    quint32 honors[2] = {0, 0};
    quint32 slamBonuses[2] = {0, 0};
    bool teamVulnerable[2] = {false, false};
};

#endif // SCORE_H
