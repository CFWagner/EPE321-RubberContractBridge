#include "score.h"
#include <QJsonArray>

// Default constructor
Score::Score() {}

// Constructor for subsequent rubber scores initialized with the back score from previous rubber scores
Score::Score(quint32 backScore[2])
{
    this->backScore[N_S] = backScore[N_S];
    this->backScore[E_W] = backScore[E_W];
}

// Update the score state based on the contract, player hands and result of the latest trick
void Score::updateScore(const Bid &contractBid, quint8 defenderTricksWon)
{

}

// Get the contract points accumulated by the specified team for the current rubber
// Dimension 0 represents each of the games in the order 1, 2, ...
// Dimension 1 represents each individual contract points entry for the given game
const QVector<quint32> Score::getContractPoints(Team team) const
{
    return contractPoints[team];
}

// Getter for the back score for the specified team
quint32 Score::getBackScore(Team team) const
{
    return backScore[team];
}

// Getter for the overtricks for the specified team
quint32 Score::getOvertricks(Team team) const
{
    return overtricks[team];
}

// Getter for the undertricks for the specified team
quint32 Score::getUndertricks(Team team) const
{
    return undertricks[team];
}

// Getter for the honors for the specified team
quint32 Score::getHonors(Team team) const
{
    return honors[team];
}

// Getter for the slam bonuses for the specified team
quint32 Score::getSlamBonuses(Team team) const
{
    return slamBonuses[team];
}

// Initialize score attributes from JSON object
void Score::read(const QJsonObject &json)
{
    // Read contractPoints array from JSON object
    QJsonArray jsonConPointsTeams = json["contractPoints"].toArray();
    for (qint8 team = N_S; team < E_W; ++ team) {
        QJsonArray jsonConPointsGames = jsonConPointsTeams[team].toArray();
        QVector<quint32> conPointsGames;
        conPointsGames.reserve(jsonConPointsGames.size());
        for (qint8 game = 0; game < jsonConPointsGames.size(); ++ game) {
            quint32 points = jsonConPointsGames[game].toInt();
            conPointsGames.append(points);
        }
        contractPoints[team] = conPointsGames;
    }

    // Read back score array from JSON object
    QJsonArray jsonBackScoreArray = json["backScore"].toArray();
    for (qint8 index = 0; index < jsonBackScoreArray.size(); ++ index) {
        bool backScoreElement = jsonBackScoreArray[index].toBool();
        backScore[index] = backScoreElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonOvertricksArray = json["Overtricks"].toArray();
    for (qint8 index = 0; index < jsonOvertricksArray.size(); ++ index) {
        bool overtricksElement = jsonOvertricksArray[index].toBool();
        overtricks[index] = overtricksElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonUndertricksArray = json["undertricks"].toArray();
    for (qint8 index = 0; index < jsonUndertricksArray.size(); ++ index) {
        bool undertricksElement = jsonUndertricksArray[index].toBool();
        undertricks[index] = undertricksElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonHonorsArray = json["honors"].toArray();
    for (qint8 index = 0; index < jsonHonorsArray.size(); ++ index) {
        bool honorsElement = jsonHonorsArray[index].toBool();
        honors[index] = honorsElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonslamBonusesArray = json["slamBonuses"].toArray();
    for (qint8 index = 0; index < jsonslamBonusesArray.size(); ++ index) {
        bool slamBonusesElement = jsonslamBonusesArray[index].toBool();
        slamBonuses[index] = slamBonusesElement;
    }
}

// Add Score instance attributes to the JSON object argument
void Score::write(QJsonObject &json) const
{
    // Add contractPoints array to JSON object
    QJsonArray jsonConPointsTeams;
    for (qint8 team = N_S; team < E_W; ++ team) {
        QVector<quint32> conPointsGames = contractPoints[team];
        QJsonArray jsonConPointsGames;
        for (qint8 game = 0; game < conPointsGames.size(); ++ game) {
            qint32 points = conPointsGames.value(game);
            jsonConPointsGames.append(points);
        }
        jsonConPointsTeams.append(jsonConPointsGames);
    }
    json["contractPoints"] = jsonConPointsTeams;

    // Add back score array to JSON object
    QJsonArray jsonBackScoreArray;
    for (const bool &backScoreElement: backScore)
        jsonBackScoreArray.append(backScoreElement);
    json["backScore"] = jsonBackScoreArray;

    // Add back score array to JSON object
    QJsonArray jsonOvertricksArray;
    for (const bool &overTricksElement: overtricks)
        jsonOvertricksArray.append(overTricksElement);
    json["overtricks"] = jsonOvertricksArray;

    // Add back score array to JSON object
    QJsonArray jsonUndertricksArray;
    for (const bool &undertricksElement: backScore)
        jsonUndertricksArray.append(undertricksElement);
    json["undertricks"] = jsonUndertricksArray;

    // Add back score array to JSON object
    QJsonArray jsonHonorsArray;
    for (const bool &honorsElement: backScore)
        jsonHonorsArray.append(honorsElement);
    json["honors"] = jsonHonorsArray;

    // Add back score array to JSON object
    QJsonArray jsonslamBonusesArray;
    for (const bool &slamBonusesElement: backScore)
        jsonslamBonusesArray.append(slamBonusesElement);
    json["slamBonuses"] = jsonslamBonusesArray;

}

// Overloaded == relational operator to compare score equality
// Two scores are equal if the contract points, back score and premium scores are equal
// and have the same order
bool Score::operator ==(const Score& score) const
{
    return contractPoints == score.contractPoints &&
            backScore[N_S] == score.backScore[N_S] &&
            backScore[E_W] == score.backScore[E_W] &&
            overtricks[N_S] == score.overtricks[N_S] &&
            overtricks[E_W] == score.overtricks[E_W] &&
            undertricks[N_S] == score.undertricks[N_S] &&
            undertricks[E_W] == score.undertricks[E_W] &&
            honors[N_S] == score.honors[N_S] &&
            honors[E_W] == score.honors[E_W] &&
            slamBonuses[N_S] == score.slamBonuses[N_S] &&
            slamBonuses[E_W] == score.slamBonuses[E_W];
}
