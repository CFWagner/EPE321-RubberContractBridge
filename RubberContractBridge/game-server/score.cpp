#include "score.h"

Score::Score()
{

}

Score::Score(quint32 backScore[2])
{

}

void Score::updateScore(Bid contractBid, quint8 defenderTricksWon)
{

}

QVector<quint32> Score::getContractPoints(Team team)
{

}

quint32 Score::getBackScore(Team team)
{

}

quint32 Score::getovertricks(Team team)
{

}

quint32 Score::getundertricks(Team team)
{

}

quint32 Score::getHonors(Team team)
{

}

quint32 Score::getSmallSlamBonuses(Team team)
{

}

quint32 Score::getGrandSlamBonuses(Team team)
{

}


void Score::read(const QJsonObject &json)
{

}

void Score::write(QJsonObject &json) const
{

}

bool Score::operator ==(const Score& score) const
{
    return true;
}
