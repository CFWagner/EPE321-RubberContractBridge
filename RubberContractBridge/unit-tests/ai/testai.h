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
    PlayerGameState player1;
    AI playerAI;
private slots:
    void testHandGenerate();
    void testMoveGenerate();
    void testBidRX();
    void testBidGenerate();
    void testBidGenerate2();
    void testMoveGanerate2();
    void testMoveGanerate3();

};

#endif // TESTAI_H
