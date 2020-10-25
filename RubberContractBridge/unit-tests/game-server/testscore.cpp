#include "testscore.h"

TestScore::TestScore(QObject *parent) : QObject(parent) {}

void TestScore::testScore()
{
    Score score1;

    // Test initialisation of score instance attributes and calculation methods
    QCOMPARE(score1.getContractPoints(N_S).size(), 1);
    QCOMPARE(score1.getContractPoints(N_S).value(0), 0);
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
    QCOMPARE(score1.getContractPoints(E_W).value(0), 0);
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

    Score score2;
    // Test equality operator
    QCOMPARE(score1, score2);

}
