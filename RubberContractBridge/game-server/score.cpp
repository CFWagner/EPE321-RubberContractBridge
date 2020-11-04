#include "score.h"
#include <QJsonArray>

// Default constructor
Score::Score() {
    contractPoints[N_S].append(0);
    contractPoints[E_W].append(0);
}

// Constructor for subsequent rubber scores initialized with the back score from previous rubber scores
Score::Score(quint32 backScore[2])
{
    contractPoints[N_S].append(0);
    contractPoints[E_W].append(0);
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
    if(contractBid.getCall() == DOUBLE_BID){
        doubled = true;
        multiplier = 2;
    }
    else if(contractBid.getCall() == REDOUBLE_BID){
        redoubled = true;
        multiplier = 4;
    }

    // Get if declaring side is vulnerable
    bool bidderVulnerable = getTeamVulnerable(biddingTeam);

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
        overtricks[biddingTeam] += overTricks * overtrickPoints;

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
        if(numUndertricks >= 4){
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

// Check if a team won the current game based on the current contract points
bool Score::isGameWinner() const
{
    return contractPoints[N_S].last() >= 100 || contractPoints[E_W].last() >= 100;
}

// Check if a team won the current rubber based on the current contract points and gamesWon
bool Score::isRubberWinner() const
{
    return getGamesWon(N_S) == 2 || getGamesWon(E_W) == 2;
}

// Get the winner of the game based on the current contract points
// Only call this function after isWinner() returns true
Team Score::getGameWinner() const
{
    if(contractPoints[N_S].last() >= 100)
        return N_S;
    else
        return E_W;
}

// Get the winner of the rubber based on the number of games won
// Only call this function after isRubberWinner() returns true
Team Score::getRubberWinner() const
{
    if(getGamesWon(N_S) == 2)
        return N_S;
    else
        return E_W;
}

// Get the winner of the match based on the contract points and premium scores
// Call this if isMatchDraw() returns false as this returns E_W as winner if draw
Team Score::getMatchWinner() const
{
    if(getTotalScore(N_S) > getTotalScore(E_W))
        return N_S;
    else
        return E_W;
}

// Gets whether the match is a draw based on the total scores
bool Score::isMatchDraw() const
{
    return getTotalScore(N_S) == getTotalScore(E_W);
}

// If isRubberWinner() returns true, returns the total scores for the finished rubber
// If isRubberWinner() returns false, returns the total scores for an unfinished rubber
// Only call this function after finaliseRubber() is called
quint32 Score::getTotalScore(Team team) const
{
    quint32 totalScore = 0;
    for(quint32 points: contractPoints[team])
        totalScore += points;
    totalScore += backScore[team];
    totalScore += overtricks[team];
    totalScore += undertricks[team];
    totalScore += honors[team];
    totalScore += slamBonuses[team];
    totalScore += doubleBonuses[team];
    totalScore += redoubleBonuses[team];
    totalScore += rubberBonuses[team];

    return totalScore;
}

// If isRubberWinner() returns true, calculates the finished rubber bonus and stores result in rubberBonus
// If isRubberWinner() returns false, calculates the unfinished rubber bonus and stores result in rubberBonus
void Score::finaliseRubber()
{
    if(isRubberWinner()){
        Team rubberWinner = getRubberWinner();
        if(getGamesWon(getOppositeTeam(rubberWinner)) == 0)
            rubberBonuses[rubberWinner] += 700;
        else
            rubberBonuses[rubberWinner] += 500;
    }
    else{
        // Check if only one side has won a game
        if(getGamesWon(N_S) == 1 && getGamesWon(E_W) == 0)
            rubberBonuses[N_S] += 300;
        else if(getGamesWon(N_S) == 0 && getGamesWon(E_W) == 1)
            rubberBonuses[E_W] += 300;
        else if(contractPoints[N_S].last() > 0 && contractPoints[E_W].last() == 0)
            rubberBonuses[N_S] += 100;
        else if(contractPoints[N_S].last() == 0 && contractPoints[E_W].last() > 0)
            rubberBonuses[E_W] += 100;
    }
}

// Close off the contract points for the current game and initialise to zero for the new game
// Only call this fuction after isWinner() returns true
// Do not call this function when creating the score object for the first time
void Score::nextGame()
{
    contractPoints[N_S].append(0);
    contractPoints[E_W].append(0);
}

// Get the opposition team of the specified team
Team Score::getOppositeTeam(Team team) const
{
    if(team == N_S)
        return E_W;
    else
        return N_S;
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

// Getter for the games won in the current rubber by the specified team
quint8 Score::getGamesWon(Team team) const
{
    quint8 gamesWon = 0;
    for(qint8 i = 0; i < contractPoints[team].size(); i++){
        if(contractPoints[team].value(i) >= 100)
            ++ gamesWon;
    }
    return gamesWon;
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

quint32 Score::getDoubleBonuses(Team team) const
{
   return doubleBonuses[team];
}

quint32 Score::getReDoubleBonuses(Team team) const
{
   return redoubleBonuses[team];
}

// Getter for the rubber bonuses for the specified team
quint32 Score::getRubberBonuses(Team team) const
{
    return rubberBonuses[team];
}

// Getter for the vulnerability status for the specified team
bool Score::getTeamVulnerable(Team team) const
{
    return getGamesWon(team) > 0;
}

// Initialize score attributes from JSON object
void Score::read(const QJsonObject &json)
{
    // Read contractPoints array from JSON object
    QJsonArray jsonConPointsTeams = json["contractPoints"].toArray();
    for (qint8 team = N_S; team <= E_W; ++ team) {
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
        qint32 backScoreElement = jsonBackScoreArray[index].toInt();
        backScore[index] = backScoreElement;
    }

    // Read overtricks array from JSON object
    QJsonArray jsonOvertricksArray = json["overtricks"].toArray();
    for (qint8 index = 0; index < jsonOvertricksArray.size(); ++ index) {
        qint32 overtricksElement = jsonOvertricksArray[index].toInt();
        overtricks[index] = overtricksElement;
    }

    // Read undertricks array from JSON object
    QJsonArray jsonUndertricksArray = json["undertricks"].toArray();
    for (qint8 index = 0; index < jsonUndertricksArray.size(); ++ index) {
        qint32 undertricksElement = jsonUndertricksArray[index].toInt();
        undertricks[index] = undertricksElement;
    }

    // Read honors array from JSON object
    QJsonArray jsonHonorsArray = json["honors"].toArray();
    for (qint8 index = 0; index < jsonHonorsArray.size(); ++ index) {
        qint32 honorsElement = jsonHonorsArray[index].toInt();
        honors[index] = honorsElement;
    }

    // Read slam array from JSON object
    QJsonArray jsonslamBonusesArray = json["slamBonuses"].toArray();
    for (qint8 index = 0; index < jsonslamBonusesArray.size(); ++ index) {
        qint32 slamBonusesElement = jsonslamBonusesArray[index].toInt();
        slamBonuses[index] = slamBonusesElement;
    }

    // Read double bonuses array from JSON object
    QJsonArray jsonDoubleBonusesArray = json["doubleBonuses"].toArray();
    for (qint8 index = 0; index < jsonDoubleBonusesArray.size(); ++ index) {
        qint32 doubleBonusesElement = jsonDoubleBonusesArray[index].toInt();
        doubleBonuses[index] = doubleBonusesElement;
    }

    // Read rubber bonuses array from JSON object
    QJsonArray jsonRubberBonusesArray = json["rubberBonuses"].toArray();
    for (qint8 index = 0; index < jsonRubberBonusesArray.size(); ++ index) {
        qint32 rubberBonusesElement = jsonRubberBonusesArray[index].toInt();
        rubberBonuses[index] = rubberBonusesElement;
    }
}

// Add Score instance attributes to the JSON object argument
void Score::write(QJsonObject &json) const
{
    // Add contractPoints array to JSON object
    QJsonArray jsonConPointsTeams;
    for (qint8 team = N_S; team <= E_W; ++ team) {
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
    for (const qint32 &backScoreElement: backScore)
        jsonBackScoreArray.append(backScoreElement);
    json["backScore"] = jsonBackScoreArray;

    // Add overtricks array to JSON object
    QJsonArray jsonOvertricksArray;
    for (const qint32 &overTricksElement: overtricks)
        jsonOvertricksArray.append(overTricksElement);
    json["overtricks"] = jsonOvertricksArray;

    // Add undertricks array to JSON object
    QJsonArray jsonUndertricksArray;
    for (const qint32 &undertricksElement: undertricks)
        jsonUndertricksArray.append(undertricksElement);
    json["undertricks"] = jsonUndertricksArray;

    // Add honors array to JSON object
    QJsonArray jsonHonorsArray;
    for (const qint32 &honorsElement: honors)
        jsonHonorsArray.append(honorsElement);
    json["honors"] = jsonHonorsArray;

    // Add slam bonus array to JSON object
    QJsonArray jsonslamBonusesArray;
    for (const qint32 &slamBonusesElement: slamBonuses)
        jsonslamBonusesArray.append(slamBonusesElement);
    json["slamBonuses"] = jsonslamBonusesArray;

    // Add double bonuses array to JSON object
    QJsonArray jsonDoubleBonusesArray;
    for (const qint32 &doubleBonusesElement: doubleBonuses)
        jsonDoubleBonusesArray.append(doubleBonusesElement);
    json["doubleBonuses"] = jsonDoubleBonusesArray;

    // Add redouble bonuses array to JSON object
    QJsonArray jsonRedoubleBonusesArray;
    for (const qint32 &redoubleBonusesElement: redoubleBonuses)
        jsonRedoubleBonusesArray.append(redoubleBonusesElement);
    json["redoubleBonuses"] = jsonRedoubleBonusesArray;

    // Add rubber bonuses array to JSON object
    QJsonArray jsonRubberBonusesArray;
    for (const qint32 &rubberBonusesElement: rubberBonuses)
        jsonRubberBonusesArray.append(rubberBonusesElement);
    json["rubberBonuses"] = jsonRubberBonusesArray;
}

// Overloaded == relational operator to compare score equality
// Two scores are equal if the contract points, back score and premium scores are equal
// and have the same order
bool Score::operator ==(const Score& score) const
{
    return contractPoints[N_S] == score.contractPoints[N_S] &&
            contractPoints[E_W] == score.contractPoints[E_W] &&
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
            doubleBonuses[N_S] == score.doubleBonuses[N_S] &&
            doubleBonuses[E_W] == score.doubleBonuses[E_W] &&
            redoubleBonuses[N_S] == score.redoubleBonuses[N_S] &&
            redoubleBonuses[E_W] == score.redoubleBonuses[E_W] &&
            rubberBonuses[N_S] == score.rubberBonuses[N_S] &&
            rubberBonuses[E_W] == score.rubberBonuses[E_W];
}
