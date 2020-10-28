#include "gui/entrywindow.h"
#include "gui/bidwindow.h"
#include <QApplication>
#include "unit-tests/game-server/testbid.h"
#include "unit-tests/game-server/testcard.h"
#include "unit-tests/game-server/testcardset.h"
#include "unit-tests/game-server/testgameserver.h"
#include "unit-tests/game-server/testplayergamestate.h"
#include "unit-tests/game-server/testscore.h"
#include "unit-tests/game-server/testserver.h"
#include "unit-tests/game-server/testservergamestate.h"

int main(int argc, char *argv[])
{
    TestBid testBid;
    QTest::qExec(&testBid);

    TestCard testCard;
    QTest::qExec(&testCard);

    TestCardSet testCardset;
    QTest::qExec(&testCardset);

    TestScore testScore;
    QTest::qExec(&testScore);

    TestPlayerGameState testPlayerGameState;
    QTest::qExec(&testPlayerGameState);

    TestServerGameState testServerGameState;
    QTest::qExec(&testServerGameState);

    TestGameServer testGameServer;
    QTest::qExec(&testGameServer);

    TestServer testServer;
    QTest::qExec(&testServer);
}
