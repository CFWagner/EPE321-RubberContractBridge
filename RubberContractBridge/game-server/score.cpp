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
void Score::updateScore(const Bid &contractBid, QMap<PlayerPosition, CardSet> playerHands, quint8 declarerTricksWon)
{
    // Get double or redouble multiplier
    qint8 multiplier;
    switch(contractBid.getCall()){
        case DOUBLE:
            multiplier = 2;
            break;
        case REDOUBLE:
            multiplier = 4;
            break;
        default:
            multiplier = 1;
            break;
    }

    // Contract was made
    if(declarerTricksWon >= contractBid.getTricksAbove() + 6){
        Team biddingTeam = contractBid.getBiddingTeam();

        // Get points won per trick
        qint8 trickPoints;
        qint8 overtrickPoints;
        switch(contractBid.getTrumpSuit()){
            // No trump and major suits
            case NONE:
            case SPADES:
            case HEARTS:
                trickPoints = 30;
                overtrickPoints = 30;
                break;
            // Minor suits
            default:
                trickPoints = 20;
                overtrickPoints = 20;
                break;
        }

        // Adjust overtrick points if doubled or redoubled
        if(contractBid.getCall() == DOUBLE || contractBid.getCall() == REDOUBLE){
            overtrickPoints = 100 * multiplier * 0.5;
            if(teamVulnerable[biddingTeam])
                overtrickPoints *= 2;
        }

        // Apply double or redouble multiplier
        trickPoints *= multiplier;

        // Apply adjustment for first trick if trump suit is no trump
        qint8 noTrumpAdjust = 0;
        if(contractBid.getTrumpSuit() == NONE)
            noTrumpAdjust = 10 * multiplier;

        // Update contract points
        contractPoints[biddingTeam].last() += (contractBid.getTricksAbove() * trickPoints) + noTrumpAdjust;

        // Update overtrick points
        qint8 overTricks = declarerTricksWon - (contractBid.getTricksAbove() + 6);
        overtricks[biddingTeam] += overTricks * trickPoints;
    }
    // Contract was not made
    else{

    }
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

// Getter for the vulnerability status for the specified team
bool Score::getTeamVulnerable(Team team) const
{
    return teamVulnerable[team];
}

// Setter for the vulnerability status for the specified team
void Score::setTeamVulnerable(Team team)
{
    teamVulnerable[team] = true;
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

    // Read team vunerable array from JSON object
    QJsonArray jsonTeamVulnerableArray = json["teamVulnerable"].toArray();
    for (qint8 index = 0; index < jsonTeamVulnerableArray.size(); ++ index) {
        bool teamVulnerableElement = jsonTeamVulnerableArray[index].toBool();
        teamVulnerable[index] = teamVulnerableElement;
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

    // Add team vunerable array to JSON object
    QJsonArray jsonTeamVulnerableArray;
    for (const bool &teamVulnerableElement: teamVulnerable)
        jsonTeamVulnerableArray.append(teamVulnerableElement);
    json["teamVulnerable"] = jsonTeamVulnerableArray;
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
            slamBonuses[E_W] == score.slamBonuses[E_W] &&
            teamVulnerable[N_S] == score.teamVulnerable[N_S] &&
            teamVulnerable[E_W] == score.teamVulnerable[E_W];
}
