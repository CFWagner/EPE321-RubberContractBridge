#include "testlobby.h"

testLobby::testLobby(QObject *parent) : QObject(parent)
{

}

void testLobby::Lobby()
{
    testserlobby.show();
    while (!testserlobby.isVisible()) {
         QTest::qWait(200);
    }
    connect(this,SIGNAL(addPlayer(QString)),&testserlobby,SLOT(addPlayer(QString)));
    connect(this,SIGNAL(removePlayer(QString)),&testserlobby,SLOT(removePlayer(QString)));
    spyaddPlayer = new QSignalSpy(this, SIGNAL(addPlayer(QString)));
    spyremovePlayer = new QSignalSpy(this, SIGNAL(removePlayer(QString)));
    //Test 1 check if signal are valid
    QVERIFY(spyaddPlayer->isValid());
    QVERIFY(spyremovePlayer->isValid());
    emit addPlayer("Stitch");
    emit addPlayer("Lydia");
    emit removePlayer("Lydia");
}
