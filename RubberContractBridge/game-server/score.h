#ifndef SCORE_H
#define SCORE_H

#include <QJsonObject>
#include "enumerations/Team.h"
#include "bid.h"

// Contains the various components of the team scores for a single rubber
class Score
{
public:
    Score();
    Score(quint32 backScore[2]);
    void updateScore(Bid contractBid, quint8 defenderTricksWon);
    QVector<quint32> getContractPoints(Team team);
    quint32 getBackScore(Team team);
    quint32 getovertricks(Team team);
    quint32 getundertricks(Team team);
    quint32 getHonors(Team team);
    quint32 getSmallSlamBonuses(Team team);
    quint32 getGrandSlamBonuses(Team team);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const Score& score) const;
private:
    QVector<QVector<quint32>> contractPoints[2];
    quint32 backScore[2];
    quint32 overtricks[2];
    quint32 undertricks[2];
    quint32 honors[2];
    quint32 smallSlamBonuses[2];
    quint32 grandSlamBonuses[2];
    bool vulnerable[2];
};

#endif // SCORE_H
