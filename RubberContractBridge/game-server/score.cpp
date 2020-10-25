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
    // Get team roles
    Team biddingTeam = contractBid.getBiddingTeam();
    Team defendingTeam;
    if(biddingTeam == N_S)
        defendingTeam = E_W;
    else
        defendingTeam = N_S;

    // Get doubled or redoubled status and multiplier
    qint8 multiplier = 1;
    bool doubled = false;
    bool redoubled = false;
    if(contractBid.getCall() == DOUBLE){
        doubled = true;
        multiplier = 2;
    }
    else if(contractBid.getCall() == REDOUBLE){
        redoubled = true;
        multiplier = 4;
    }

    // Get if declaring side is vulnerable
    bool bidderVulnerable = teamVulnerable[biddingTeam];

    // Contract was made
    if(declarerTricksWon >= contractBid.getTricksAbove() + 6){
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
        if(doubled || redoubled){
            overtrickPoints = 100 * multiplier * 0.5;
            if(bidderVulnerable)
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

        // Apply slam bonuses
        if(declarerTricksWon == 12){
            // Small slam
            if(bidderVulnerable)
                slamBonuses[biddingTeam] += 750;
            else
                slamBonuses[biddingTeam] += 500;
        }
        else if(declarerTricksWon == 13){
            // Grand slam
            if(bidderVulnerable)
                slamBonuses[biddingTeam] += 1500;
            else
                slamBonuses[biddingTeam] += 1000;
        }

        // Apply double or redoubled bonus
        if(doubled)
            doubleBonuses[biddingTeam] += 50;
        else if (redoubled)
            redoubleBonuses[biddingTeam] += 100;

    }
    // Contract was not made
    else{
        qint8 numUndertricks = contractBid.getTricksAbove() + 6 - declarerTricksWon;

        // Apply undertrick penalty points for 1st undertrick
        if(bidderVulnerable){
            if(doubled)
                undertricks[defendingTeam] += 200;
            else if(redoubled)
                undertricks[defendingTeam] += 400;
            else
                undertricks[defendingTeam] += 100;
        }
        else{
            if(doubled)
                undertricks[defendingTeam] += 100;
            else if(redoubled)
                undertricks[defendingTeam] += 200;
            else
                undertricks[defendingTeam] += 50;
        }

        // Apply undertrick penalty points for 2nd and 3rd undertrick
        if(numUndertricks >= 2){
            // Get multiplier for 2nd trick or 2nd trick and third trick present
            qint8 numTricks;
            if(numUndertricks == 2)
                numTricks = 1;
            else if(numUndertricks > 2)
                numTricks = 2;

            // Apply penalty points
            if(bidderVulnerable){
                if(doubled)
                    undertricks[defendingTeam] += 300 * numTricks;
                else if(redoubled)
                    undertricks[defendingTeam] += 600 * numTricks;
                else
                    undertricks[defendingTeam] += 100 * numTricks;
            }
            else{
                if(doubled)
                    undertricks[defendingTeam] += 200 * numTricks;
                else if(redoubled)
                    undertricks[defendingTeam] += 400 * numTricks;
                else
                    undertricks[defendingTeam] += 50 * numTricks;
            }
        }

        // Apply undertrick penalty points for 4th and subsequent undertricks
        // Apply undertrick penalty points for 2nd and 3rd undertrick
        if(numUndertricks > 1){
            // Get multiplier for number of tricks above and including 4
            qint8 numTricks = numUndertricks - 3;

            // Apply penalty points
            if(bidderVulnerable){
                if(doubled)
                    undertricks[defendingTeam] += 300 * numTricks;
                else if(redoubled)
                    undertricks[defendingTeam] += 600 * numTricks;
                else
                    undertricks[defendingTeam] += 100 * numTricks;
            }
            else{
                if(doubled)
                    undertricks[defendingTeam] += 300 * numTricks;
                else if(redoubled)
                    undertricks[defendingTeam] += 600 * numTricks;
                else
                    undertricks[defendingTeam] += 50 * numTricks;
            }
        }
    }

    // Check player hands for honors bonus
    if(contractBid.getTrumpSuit() == NONE){
        for(qint8 position = NORTH; position <= WEST; ++ position){
            PlayerPosition playerPosition = PlayerPosition(position);
            Team team = getTeam(playerPosition);
            const CardSet &hand = playerHands.value(playerPosition);

            // Check if player has all 4 aces for no trump
            if(hand.containsCard(Card(DIAMONDS, ACE))
                    && hand.containsCard(Card(HEARTS, ACE))
                    && hand.containsCard(Card(DIAMONDS, ACE))
                    && hand.containsCard(Card(HEARTS, ACE))){
                honors[team] += 150;
            }
        }
    }
    else{
        for(qint8 position = NORTH; position <= WEST; ++ position){
            PlayerPosition playerPosition = PlayerPosition(position);
            Team team = getTeam(playerPosition);
            const CardSet &hand = playerHands.value(playerPosition);
            CardSuit trumpSuit = contractBid.getTrumpSuit();

            // Check how many of trump suit honors player holds
            qint8 honorsCount = 0;
            if(hand.containsCard(Card(trumpSuit, TEN)))
                ++ honorsCount;
            if(hand.containsCard(Card(trumpSuit, JACK)))
                ++ honorsCount;
            if(hand.containsCard(Card(trumpSuit, QUEEN)))
                ++ honorsCount;
            if(hand.containsCard(Card(trumpSuit, KING)))
                ++ honorsCount;
            if(hand.containsCard(Card(trumpSuit, ACE)))
                ++ honorsCount;

            // Apply honors bonuses
            if(honorsCount == 4)
                honors[team] += 100;
            else if(honorsCount == 5)
                honors[team] += 150;
        }
    }

}

// Get the team the player belongs to based on their position
Team Score::getTeam(PlayerPosition position) const
{
    switch (position) {
        case NORTH:
        case SOUTH:
            return N_S;
        default:
            return E_W;
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

    // Read games won array from JSON object
    QJsonArray jsonGamesWonArray = json["gamesWon"].toArray();
    for (qint8 index = 0; index < jsonGamesWonArray.size(); ++ index) {
        bool gamesWonElement = jsonGamesWonArray[index].toBool();
        gamesWon[index] = gamesWonElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonBackScoreArray = json["backScore"].toArray();
    for (qint8 index = 0; index < jsonBackScoreArray.size(); ++ index) {
        bool backScoreElement = jsonBackScoreArray[index].toBool();
        backScore[index] = backScoreElement;
    }

    // Read back score array from JSON object
    QJsonArray jsonOvertricksArray = json["overtricks"].toArray();
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

    // Read double bonuses array from JSON object
    QJsonArray jsonDoubleBonusesArray = json["doubleBonuses"].toArray();
    for (qint8 index = 0; index < jsonDoubleBonusesArray.size(); ++ index) {
        bool doubleBonusesElement = jsonDoubleBonusesArray[index].toBool();
        doubleBonuses[index] = doubleBonusesElement;
    }

    // Read redouble bonuses array from JSON object
    QJsonArray jsonRedoubleBonusesArray = json["redoubleBonuses"].toArray();
    for (qint8 index = 0; index < jsonRedoubleBonusesArray.size(); ++ index) {
        bool redoubleBonusesElement = jsonRedoubleBonusesArray[index].toBool();
        redoubleBonuses[index] = redoubleBonusesElement;
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

    // Add games won array to JSON object
    QJsonArray jsonGamesWonArray;
    for (const bool &gamesWonElement: gamesWon)
        jsonGamesWonArray.append(gamesWonElement);
    json["gamesWon"] = jsonGamesWonArray;

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

    // Add double bonuses array to JSON object
    QJsonArray jsonDoubleBonusesArray;
    for (const bool &doubleBonusesElement: doubleBonuses)
        jsonDoubleBonusesArray.append(doubleBonusesElement);
    json["doubleBonuses"] = jsonDoubleBonusesArray;

    // Add redouble bonuses array to JSON object
    QJsonArray jsonRedoubleBonusesArray;
    for (const bool &redoubleBonusesElement: redoubleBonuses)
        jsonRedoubleBonusesArray.append(redoubleBonusesElement);
    json["redoubleBonuses"] = jsonRedoubleBonusesArray;
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
