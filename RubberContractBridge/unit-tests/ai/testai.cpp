#include "testai.h"
#include <QtTest/QtTest>

testai::testai(QObject *parent) : QObject(parent)
{
}


void testai::testHandGenerate()
{ 
    AI playerAI;
    playerAI = AI();
    PlayerGameState player1;
    player1 = PlayerGameState();
    playerAI.updateGameState(player1);
    CardSet received;
    received = playerAI.getHand();
    qDebug() << "Testing hand length";
    QCOMPARE(received.getCardCount(),5);

}
