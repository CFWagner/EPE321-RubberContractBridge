#include "testscore.h"

TestScore::TestScore(QObject *parent) : QObject(parent) {}

void TestScore::testScore()
{
    // Test initialisation of score instance attributes and calculation methods
    Score score1;
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).last(), 0);
    QCOMPARE(score1.getGamesWon(N_S), 0);
    QCOMPARE(score1.getBackScore(N_S), 0);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 0);
    QCOMPARE(score1.getSlamBonuses(N_S), 0);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), false);
    QCOMPARE(score1.getTotalScore(N_S), 0);
    QCOMPARE(score1.getContractPoints(E_W).size(), 1);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 0);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 0);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), false);
    QCOMPARE(score1.getTotalScore(E_W), 0);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

    // Test equality operator
    Score score2;
    QCOMPARE(score1, score2);

    // Test attributes after score update with no trump and 1 odd tricks
    Bid contractBid(NORTH, NONE, 1);
    score1.updateScore(contractBid, getNoHonorsHand(), 7);
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).last(), 40);
    QCOMPARE(score1.getGamesWon(N_S), 0);
    QCOMPARE(score1.getBackScore(N_S), 0);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 0);
    QCOMPARE(score1.getSlamBonuses(N_S), 0);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), false);
    QCOMPARE(score1.getTotalScore(N_S), 40);
    QCOMPARE(score1.getContractPoints(E_W).size(), 1);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 0);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 0);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), false);
    QCOMPARE(score1.getTotalScore(E_W), 0);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

    // Test attributes after score update with no trump and 3 odd tricks and 1 overtrick
    contractBid = Bid(WEST, NONE, 3);
    score1.updateScore(contractBid, getNoHonorsHand(), 10);
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).last(), 40);
    QCOMPARE(score1.getGamesWon(N_S), 0);
    QCOMPARE(score1.getBackScore(N_S), 0);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 0);
    QCOMPARE(score1.getSlamBonuses(N_S), 0);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), false);
    QCOMPARE(score1.getTotalScore(N_S), 40);
    QCOMPARE(score1.getContractPoints(E_W).size(), 1);
    QCOMPARE(score1.getContractPoints(E_W).last(), 100);
    QCOMPARE(score1.getGamesWon(E_W), 1);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 30);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), true);
    QCOMPARE(score1.getTotalScore(E_W), 130);
    QCOMPARE(score1.isGameWinner(), true);
    QCOMPARE(score1.isRubberWinner(), false);
    QCOMPARE(score1.getGameWinner(), E_W);

    // Test attributes after starting the next game
    score1.nextGame();
    QCOMPARE(score1.getContractPoints(N_S).size(), 2);
    QCOMPARE(score1.getContractPoints(N_S).last(), 0);
    QCOMPARE(score1.getContractPoints(E_W).size(), 2);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

    // Test attributes after score update with no trump honors hand and 6 odd tricks for small slam
    contractBid = Bid(SOUTH, NONE, 6);
    score1.updateScore(contractBid, getNSNoTrumpHonorsHand(), 12);
    QCOMPARE(score1.getContractPoints(N_S).size(), 2);
    QCOMPARE(score1.getContractPoints(N_S).last(), 190);
    QCOMPARE(score1.getGamesWon(N_S), 1);
    QCOMPARE(score1.getBackScore(N_S), 0);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 150);
    QCOMPARE(score1.getSlamBonuses(N_S), 500);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), true);
    QCOMPARE(score1.getTotalScore(N_S), 880);
    QCOMPARE(score1.getContractPoints(E_W).size(), 2);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 1);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 30);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), true);
    QCOMPARE(score1.getTotalScore(E_W), 130);
    QCOMPARE(score1.isGameWinner(), true);
    QCOMPARE(score1.isRubberWinner(), false);
    QCOMPARE(score1.getGameWinner(), N_S);

    // Test attributes after starting the next game
    score1.nextGame();
    QCOMPARE(score1.getContractPoints(N_S).size(), 3);
    QCOMPARE(score1.getContractPoints(N_S).last(), 0);
    QCOMPARE(score1.getContractPoints(E_W).size(), 3);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

    // Test attributes after score update with 4 trump clubs honors hand and 7 odd tricks for grand slam
    contractBid = Bid(NORTH, CLUBS, 7);
    score1.updateScore(contractBid, getNSClubs4HonorsHand(), 13);
    QCOMPARE(score1.getContractPoints(N_S).size(), 3);
    QCOMPARE(score1.getContractPoints(N_S).last(), 140);
    QCOMPARE(score1.getGamesWon(N_S), 2);
    QCOMPARE(score1.getBackScore(N_S), 0);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 250);
    QCOMPARE(score1.getSlamBonuses(N_S), 2000);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), true);
    QCOMPARE(score1.getTotalScore(N_S), 2620);
    QCOMPARE(score1.getContractPoints(E_W).size(), 3);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 1);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 30);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), true);
    QCOMPARE(score1.getTotalScore(E_W), 130);
    QCOMPARE(score1.isGameWinner(), true);
    QCOMPARE(score1.isRubberWinner(), true);
    QCOMPARE(score1.getGameWinner(), N_S);

    // Test attributes after finalising the rubber for a complete rubber
    score1.finaliseRubber();
    QCOMPARE(score1.getTotalScore(N_S), 3120);
    QCOMPARE(score1.getTotalScore(E_W), 130);
    QCOMPARE(score1.isMatchDraw(), false);
    QCOMPARE(score1.getRubberWinner(), N_S);

    // Generate QJsonObject instance from Score object
    QJsonObject jsonScore;
    score1.write(jsonScore);

    // Initialize Score object using QJsonObject instance and test for before and after equality
    score2.read(jsonScore);
    QCOMPARE(score1 == score2, true);

    // Create new score instance for next rubber with back score
    quint32 backScore[2] = {2990, 0};
    score1 = Score(backScore);

    // Test back score initialisation of score instance attributes and calculation methods
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).last(), 0);
    QCOMPARE(score1.getGamesWon(N_S), 0);
    QCOMPARE(score1.getBackScore(N_S), 2990);
    QCOMPARE(score1.getOvertricks(N_S), 0);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 0);
    QCOMPARE(score1.getSlamBonuses(N_S), 0);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), false);
    QCOMPARE(score1.getTotalScore(N_S), 2990);
    QCOMPARE(score1.getContractPoints(E_W).size(), 1);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 0);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 0);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 0);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), false);
    QCOMPARE(score1.getTotalScore(E_W), 0);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

    // Test attributes after score update with 5 trump spades honors 1 odd trick and 2 overtricks doubled
    contractBid = Bid(NORTH, DIAMONDS, 1);
    contractBid.setCall(DOUBLE_BID);
    score1.updateScore(contractBid, getEWSpades5HonorsHand(), 9);
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).last(), 40);
    QCOMPARE(score1.getGamesWon(N_S), 0);
    QCOMPARE(score1.getBackScore(N_S), 2990);
    QCOMPARE(score1.getOvertricks(N_S), 200);
    QCOMPARE(score1.getUndertricks(N_S), 0);
    QCOMPARE(score1.getHonors(N_S), 0);
    QCOMPARE(score1.getSlamBonuses(N_S), 0);
    QCOMPARE(score1.getRubberBonuses(N_S), 0);
    QCOMPARE(score1.getTeamVulnerable(N_S), false);
    QCOMPARE(score1.getTotalScore(N_S), 3280);
    QCOMPARE(score1.getContractPoints(E_W).size(), 1);
    QCOMPARE(score1.getContractPoints(E_W).last(), 0);
    QCOMPARE(score1.getGamesWon(E_W), 0);
    QCOMPARE(score1.getBackScore(E_W), 0);
    QCOMPARE(score1.getOvertricks(E_W), 0);
    QCOMPARE(score1.getUndertricks(E_W), 0);
    QCOMPARE(score1.getHonors(E_W), 150);
    QCOMPARE(score1.getSlamBonuses(E_W), 0);
    QCOMPARE(score1.getRubberBonuses(E_W), 0);
    QCOMPARE(score1.getTeamVulnerable(E_W), false);
    QCOMPARE(score1.getTotalScore(E_W), 150);
    QCOMPARE(score1.isGameWinner(), false);
    QCOMPARE(score1.isRubberWinner(), false);

}

// Get hand with no honors
QMap<PlayerPosition, CardSet> TestScore::getNoHonorsHand() const
{
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet northCardSet;
    CardSet eastCardSet;
    CardSet southCardSet;
    CardSet westCardSet;

    northCardSet.addCard(Card(SPADES, ACE));
    northCardSet.addCard(Card(HEARTS, ACE));
    northCardSet.addCard(Card(CLUBS, ACE));
    northCardSet.addCard(Card(DIAMONDS, QUEEN));
    northCardSet.addCard(Card(SPADES, FIVE));
    northCardSet.addCard(Card(SPADES, SIX));
    northCardSet.addCard(Card(SPADES, SEVEN));
    northCardSet.addCard(Card(SPADES, EIGHT));
    northCardSet.addCard(Card(SPADES, NINE));
    northCardSet.addCard(Card(SPADES, TEN));
    northCardSet.addCard(Card(SPADES, JACK));
    northCardSet.addCard(Card(HEARTS, KING));
    northCardSet.addCard(Card(CLUBS, KING));

    eastCardSet.addCard(Card(SPADES, TWO));
    eastCardSet.addCard(Card(HEARTS, TWO));
    eastCardSet.addCard(Card(HEARTS, THREE));
    eastCardSet.addCard(Card(HEARTS, FOUR));
    eastCardSet.addCard(Card(HEARTS, FIVE));
    eastCardSet.addCard(Card(HEARTS, SIX));
    eastCardSet.addCard(Card(HEARTS, SEVEN));
    eastCardSet.addCard(Card(HEARTS, EIGHT));
    eastCardSet.addCard(Card(HEARTS, NINE));
    eastCardSet.addCard(Card(HEARTS, TEN));
    eastCardSet.addCard(Card(DIAMONDS, TEN));
    eastCardSet.addCard(Card(HEARTS, QUEEN));
    eastCardSet.addCard(Card(DIAMONDS, ACE));

    southCardSet.addCard(Card(SPADES, THREE));
    southCardSet.addCard(Card(CLUBS, TWO));
    southCardSet.addCard(Card(CLUBS, THREE));
    southCardSet.addCard(Card(CLUBS, FOUR));
    southCardSet.addCard(Card(CLUBS, FIVE));
    southCardSet.addCard(Card(CLUBS, SIX));
    southCardSet.addCard(Card(CLUBS, SEVEN));
    southCardSet.addCard(Card(CLUBS, EIGHT));
    southCardSet.addCard(Card(CLUBS, NINE));
    southCardSet.addCard(Card(CLUBS, TEN));
    southCardSet.addCard(Card(SPADES, QUEEN));
    southCardSet.addCard(Card(CLUBS, QUEEN));
    southCardSet.addCard(Card(SPADES, KING));

    westCardSet.addCard(Card(SPADES, FOUR));
    westCardSet.addCard(Card(DIAMONDS, TWO));
    westCardSet.addCard(Card(DIAMONDS, THREE));
    westCardSet.addCard(Card(DIAMONDS, FOUR));
    westCardSet.addCard(Card(DIAMONDS, FIVE));
    westCardSet.addCard(Card(DIAMONDS, SIX));
    westCardSet.addCard(Card(DIAMONDS, SEVEN));
    westCardSet.addCard(Card(DIAMONDS, EIGHT));
    westCardSet.addCard(Card(DIAMONDS, NINE));
    westCardSet.addCard(Card(CLUBS, JACK));
    westCardSet.addCard(Card(DIAMONDS, JACK));
    westCardSet.addCard(Card(HEARTS, JACK));
    westCardSet.addCard(Card(DIAMONDS, KING));

    playerHands.insert(NORTH, northCardSet);
    playerHands.insert(EAST, eastCardSet);
    playerHands.insert(SOUTH, southCardSet);
    playerHands.insert(WEST, westCardSet);

    return playerHands;
}

// Get set of hands where a team member of N_S has no trump honors
QMap<PlayerPosition, CardSet> TestScore::getNSNoTrumpHonorsHand() const
{
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet northCardSet;
    CardSet eastCardSet;
    CardSet southCardSet;
    CardSet westCardSet;

    northCardSet.addCard(Card(SPADES, ACE));
    northCardSet.addCard(Card(HEARTS, ACE));
    northCardSet.addCard(Card(CLUBS, ACE));
    northCardSet.addCard(Card(DIAMONDS, ACE));
    northCardSet.addCard(Card(SPADES, FIVE));
    northCardSet.addCard(Card(SPADES, SIX));
    northCardSet.addCard(Card(SPADES, SEVEN));
    northCardSet.addCard(Card(SPADES, EIGHT));
    northCardSet.addCard(Card(SPADES, NINE));
    northCardSet.addCard(Card(SPADES, TEN));
    northCardSet.addCard(Card(SPADES, JACK));
    northCardSet.addCard(Card(SPADES, QUEEN));
    northCardSet.addCard(Card(SPADES, KING));

    eastCardSet.addCard(Card(SPADES, TWO));
    eastCardSet.addCard(Card(HEARTS, TWO));
    eastCardSet.addCard(Card(HEARTS, THREE));
    eastCardSet.addCard(Card(HEARTS, FOUR));
    eastCardSet.addCard(Card(HEARTS, FIVE));
    eastCardSet.addCard(Card(HEARTS, SIX));
    eastCardSet.addCard(Card(HEARTS, SEVEN));
    eastCardSet.addCard(Card(HEARTS, EIGHT));
    eastCardSet.addCard(Card(HEARTS, NINE));
    eastCardSet.addCard(Card(HEARTS, TEN));
    eastCardSet.addCard(Card(HEARTS, JACK));
    eastCardSet.addCard(Card(HEARTS, QUEEN));
    eastCardSet.addCard(Card(HEARTS, KING));

    southCardSet.addCard(Card(SPADES, THREE));
    southCardSet.addCard(Card(CLUBS, TWO));
    southCardSet.addCard(Card(CLUBS, THREE));
    southCardSet.addCard(Card(CLUBS, FOUR));
    southCardSet.addCard(Card(CLUBS, FIVE));
    southCardSet.addCard(Card(CLUBS, SIX));
    southCardSet.addCard(Card(CLUBS, SEVEN));
    southCardSet.addCard(Card(CLUBS, EIGHT));
    southCardSet.addCard(Card(CLUBS, NINE));
    southCardSet.addCard(Card(CLUBS, TEN));
    southCardSet.addCard(Card(CLUBS, JACK));
    southCardSet.addCard(Card(CLUBS, QUEEN));
    southCardSet.addCard(Card(CLUBS, KING));

    westCardSet.addCard(Card(SPADES, FOUR));
    westCardSet.addCard(Card(DIAMONDS, TWO));
    westCardSet.addCard(Card(DIAMONDS, THREE));
    westCardSet.addCard(Card(DIAMONDS, FOUR));
    westCardSet.addCard(Card(DIAMONDS, FIVE));
    westCardSet.addCard(Card(DIAMONDS, SIX));
    westCardSet.addCard(Card(DIAMONDS, SEVEN));
    westCardSet.addCard(Card(DIAMONDS, EIGHT));
    westCardSet.addCard(Card(DIAMONDS, NINE));
    westCardSet.addCard(Card(DIAMONDS, TEN));
    westCardSet.addCard(Card(DIAMONDS, JACK));
    westCardSet.addCard(Card(DIAMONDS, QUEEN));
    westCardSet.addCard(Card(DIAMONDS, KING));

    playerHands.insert(NORTH, northCardSet);
    playerHands.insert(EAST, eastCardSet);
    playerHands.insert(SOUTH, southCardSet);
    playerHands.insert(WEST, westCardSet);

    return playerHands;
}

// Get set of hands where a team member of N_S has 4 clubs honors
QMap<PlayerPosition, CardSet> TestScore::getNSClubs4HonorsHand() const
{
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet northCardSet;
    CardSet eastCardSet;
    CardSet southCardSet;
    CardSet westCardSet;

    northCardSet.addCard(Card(SPADES, ACE));
    northCardSet.addCard(Card(SPADES, TWO));
    northCardSet.addCard(Card(SPADES, THREE));
    northCardSet.addCard(Card(SPADES, FOUR));
    northCardSet.addCard(Card(SPADES, FIVE));
    northCardSet.addCard(Card(SPADES, SIX));
    northCardSet.addCard(Card(SPADES, SEVEN));
    northCardSet.addCard(Card(SPADES, EIGHT));
    northCardSet.addCard(Card(SPADES, NINE));
    northCardSet.addCard(Card(SPADES, TEN));
    northCardSet.addCard(Card(SPADES, JACK));
    northCardSet.addCard(Card(SPADES, QUEEN));
    northCardSet.addCard(Card(SPADES, KING));

    eastCardSet.addCard(Card(HEARTS, ACE));
    eastCardSet.addCard(Card(HEARTS, TWO));
    eastCardSet.addCard(Card(HEARTS, THREE));
    eastCardSet.addCard(Card(HEARTS, FOUR));
    eastCardSet.addCard(Card(HEARTS, FIVE));
    eastCardSet.addCard(Card(HEARTS, SIX));
    eastCardSet.addCard(Card(HEARTS, SEVEN));
    eastCardSet.addCard(Card(HEARTS, EIGHT));
    eastCardSet.addCard(Card(HEARTS, NINE));
    eastCardSet.addCard(Card(HEARTS, TEN));
    eastCardSet.addCard(Card(HEARTS, JACK));
    eastCardSet.addCard(Card(HEARTS, QUEEN));
    eastCardSet.addCard(Card(HEARTS, KING));

    southCardSet.addCard(Card(CLUBS, ACE));
    southCardSet.addCard(Card(CLUBS, TWO));
    southCardSet.addCard(Card(CLUBS, THREE));
    southCardSet.addCard(Card(CLUBS, FOUR));
    southCardSet.addCard(Card(CLUBS, FIVE));
    southCardSet.addCard(Card(CLUBS, SIX));
    southCardSet.addCard(Card(CLUBS, SEVEN));
    southCardSet.addCard(Card(CLUBS, EIGHT));
    southCardSet.addCard(Card(CLUBS, NINE));
    southCardSet.addCard(Card(DIAMONDS, TEN));
    southCardSet.addCard(Card(CLUBS, JACK));
    southCardSet.addCard(Card(CLUBS, QUEEN));
    southCardSet.addCard(Card(CLUBS, KING));

    westCardSet.addCard(Card(DIAMONDS, ACE));
    westCardSet.addCard(Card(DIAMONDS, TWO));
    westCardSet.addCard(Card(DIAMONDS, THREE));
    westCardSet.addCard(Card(DIAMONDS, FOUR));
    westCardSet.addCard(Card(DIAMONDS, FIVE));
    westCardSet.addCard(Card(DIAMONDS, SIX));
    westCardSet.addCard(Card(DIAMONDS, SEVEN));
    westCardSet.addCard(Card(DIAMONDS, EIGHT));
    westCardSet.addCard(Card(DIAMONDS, NINE));
    westCardSet.addCard(Card(CLUBS, TEN));
    westCardSet.addCard(Card(DIAMONDS, JACK));
    westCardSet.addCard(Card(DIAMONDS, QUEEN));
    westCardSet.addCard(Card(DIAMONDS, KING));

    playerHands.insert(NORTH, northCardSet);
    playerHands.insert(EAST, eastCardSet);
    playerHands.insert(SOUTH, southCardSet);
    playerHands.insert(WEST, westCardSet);

    return playerHands;
}

// Get set of hands where a team member of E_W has 5 diamonds honors
QMap<PlayerPosition, CardSet> TestScore::getEWSpades5HonorsHand() const
{
    QMap<PlayerPosition, CardSet> playerHands;
    CardSet northCardSet;
    CardSet eastCardSet;
    CardSet southCardSet;
    CardSet westCardSet;

    northCardSet.addCard(Card(SPADES, ACE));
    northCardSet.addCard(Card(SPADES, TWO));
    northCardSet.addCard(Card(SPADES, THREE));
    northCardSet.addCard(Card(SPADES, FOUR));
    northCardSet.addCard(Card(SPADES, FIVE));
    northCardSet.addCard(Card(SPADES, SIX));
    northCardSet.addCard(Card(SPADES, SEVEN));
    northCardSet.addCard(Card(SPADES, EIGHT));
    northCardSet.addCard(Card(SPADES, NINE));
    northCardSet.addCard(Card(SPADES, TEN));
    northCardSet.addCard(Card(SPADES, JACK));
    northCardSet.addCard(Card(HEARTS, QUEEN));
    northCardSet.addCard(Card(HEARTS, JACK));

    eastCardSet.addCard(Card(HEARTS, ACE));
    eastCardSet.addCard(Card(HEARTS, TWO));
    eastCardSet.addCard(Card(HEARTS, THREE));
    eastCardSet.addCard(Card(HEARTS, FOUR));
    eastCardSet.addCard(Card(HEARTS, FIVE));
    eastCardSet.addCard(Card(HEARTS, SIX));
    eastCardSet.addCard(Card(HEARTS, SEVEN));
    eastCardSet.addCard(Card(HEARTS, EIGHT));
    eastCardSet.addCard(Card(HEARTS, NINE));
    eastCardSet.addCard(Card(HEARTS, TEN));
    eastCardSet.addCard(Card(SPADES, KING));
    eastCardSet.addCard(Card(SPADES, QUEEN));
    eastCardSet.addCard(Card(CLUBS, KING));

    southCardSet.addCard(Card(CLUBS, ACE));
    southCardSet.addCard(Card(CLUBS, TWO));
    southCardSet.addCard(Card(CLUBS, THREE));
    southCardSet.addCard(Card(CLUBS, FOUR));
    southCardSet.addCard(Card(CLUBS, FIVE));
    southCardSet.addCard(Card(CLUBS, SIX));
    southCardSet.addCard(Card(CLUBS, SEVEN));
    southCardSet.addCard(Card(CLUBS, EIGHT));
    southCardSet.addCard(Card(CLUBS, NINE));
    southCardSet.addCard(Card(CLUBS, TEN));
    southCardSet.addCard(Card(CLUBS, JACK));
    southCardSet.addCard(Card(CLUBS, QUEEN));
    southCardSet.addCard(Card(HEARTS, KING));

    westCardSet.addCard(Card(DIAMONDS, ACE));
    westCardSet.addCard(Card(DIAMONDS, TWO));
    westCardSet.addCard(Card(DIAMONDS, THREE));
    westCardSet.addCard(Card(DIAMONDS, FOUR));
    westCardSet.addCard(Card(DIAMONDS, FIVE));
    westCardSet.addCard(Card(DIAMONDS, SIX));
    westCardSet.addCard(Card(DIAMONDS, SEVEN));
    westCardSet.addCard(Card(DIAMONDS, EIGHT));
    westCardSet.addCard(Card(DIAMONDS, NINE));
    westCardSet.addCard(Card(DIAMONDS, TEN));
    westCardSet.addCard(Card(DIAMONDS, JACK));
    westCardSet.addCard(Card(DIAMONDS, QUEEN));
    westCardSet.addCard(Card(DIAMONDS, KING));

    playerHands.insert(NORTH, northCardSet);
    playerHands.insert(EAST, eastCardSet);
    playerHands.insert(SOUTH, southCardSet);
    playerHands.insert(WEST, westCardSet);

    return playerHands;
}
