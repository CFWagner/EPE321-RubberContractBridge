#ifndef TESTAI_H
#define TESTAI_H
#include "ai/ai.h"
#include <QtTest>
class testai : public QObject
{
    Q_OBJECT
public:
    explicit testai(QObject *parent = nullptr);
    void setInitial();
    void setInitial2();
    void setInitial3();
    void setInitial4();
    void setInitial5();
    void setInitial6();
    void setInitial7();
    PlayerGameState player1;
    AI playerAI;
    float calculateSTD(float data[], int length);
    uint32_t seed = 0;
    uint32_t random();
    float rangeGen(float min, float max);
    float testGeneratorNoSeed();
    float testGeneratorSeeded();
    float generatesNormalDistribution();
    float calculateMean(float data[], int length);
    float UniformMean;
    float SeedMean;
    float NoSeedMean;
private slots:
    void testHandGenerate();
    void testMoveGenerate();
    void testBidRX();
    void testBidGenerate();
    void testBidGenerate2();
    void testMoveGanerate2();
    void testMoveGanerate3();
    void testMoveGanerate4();
    void testMoveGanerate5();
    void testDeckGeneration();
    void testDeckRemoval();
    void testingGenerator();
    void testingRecovery();
    void testingBidListGenerate();


};

#endif // TESTAI_H
