//Unit tests
#include "unit-tests/game-server/testbid.h"
#include "unit-tests/game-server/testcard.h"
#include "unit-tests/game-server/testcardset.h"
#include "unit-tests/game-server/testservergamestate.h"
#include "unit-tests/game-server/testplayergamestate.h"

int main(int argc, char *argv[])
{
    //Unit tests
    TestBid testBid;
    QTest::qExec(&testBid);
    TestCard testCard;
    QTest::qExec(&testCard);
    TestCardSet testCardSet;
    QTest::qExec(&testCardSet);
    TestServerGameState testServerGameState;
    QTest::qExec(&testServerGameState);
    TestPlayerGameState testPlayerGameState;
    QTest::qExec(&testPlayerGameState);
}
