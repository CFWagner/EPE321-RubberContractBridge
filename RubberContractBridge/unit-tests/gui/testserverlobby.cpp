#include "testserverlobby.h"

testServerLobby::testServerLobby(QObject *parent) : QObject(parent)
{

}

testServerLobby::~testServerLobby()
{

}

void testServerLobby::testSerLob()
{
    testSLob = new ServerLobby();
    createServer = new Server();
    while (!testSLob->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);
    QVERIFY(testSLob->isVisible()); // Check if visable.

    //Signals check
    startGame = new QSignalSpy(testSLob, SIGNAL(playersSelected(QVector<QString>)));
    addPlayerP = new QSignalSpy(this, SIGNAL(playerJoined (QString)));
    removePlayerP = new QSignalSpy(this, SIGNAL(playerDisconnected (QString)));
    QVERIFY(startGame->isValid());
    QVERIFY(addPlayerP->isValid());
    QVERIFY(removePlayerP->isValid());
    connect(testSLob,&ServerLobby::playersSelected,createServer,&Server::playersSelected);
    connect(this,&testServerLobby::playerJoined,testSLob,&ServerLobby::addPlayer);
    connect(this,&testServerLobby::playerDisconnected,testSLob,&ServerLobby::removePlayer);
}
