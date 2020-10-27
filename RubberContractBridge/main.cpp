#include <QApplication>
#include "unit-tests/game-server/testgameserver.h"

int main(int argc, char *argv[])
{
    TestGameServer testGameServer;
    QTest::qExec(&testGameServer);
}
