#include "testserverlobby.h"

testServerLobby::testServerLobby(QObject *parent) : QObject(parent)
{

}

testServerLobby::~testServerLobby()
{
    addPlayerP->deleteLater();
    removePlayerP->deleteLater();
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

    //Add players and remove players to the pool.
    QListWidget *playerList = testSLob->findChild<QListWidget *>("playerList");
    QTest::qWait(500);

    emit playerJoined("Stitch");
    QList<QVariant> pJoined = addPlayerP->takeFirst();
    QVERIFY(qvariant_cast<QString>(pJoined.at(0)) == playerList->itemAt(10,10)->text());
    QTest::qWait(500);

    emit playerJoined("Lydia");
    pJoined = addPlayerP->takeFirst();
    QVERIFY(qvariant_cast<QString>(pJoined.at(0)) == playerList->itemAt(10,20)->text());
    QTest::qWait(500);

    emit playerJoined("Baster");
    pJoined = addPlayerP->takeFirst();
    QVERIFY(qvariant_cast<QString>(pJoined.at(0)) == playerList->itemAt(10,35)->text());
    QTest::qWait(500);

    emit playerDisconnected("Lydia");
    QList<QVariant> pLeave = removePlayerP->takeFirst();
    QVERIFY(qvariant_cast<QString>(pLeave.at(0)) != playerList->itemAt(10,20)->text());
    QTest::qWait(500);

    //Add players to active lobby.
    QTest::mouseMove (testSLob, QPoint(60,80),-1);
    QTest::qWait(500);
    QTest::mouseClick (playerList->viewport(), Qt::LeftButton, Qt::ControlModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QTest::mouseMove (playerList->viewport(), QPoint(10,20),-1);
    QTest::qWait(500);
    QTest::mouseClick (playerList->viewport(), Qt::LeftButton, Qt::ControlModifier, QPoint(10,20),100);
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(150,350),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLob->childAt(QPoint(150,350)), Qt::LeftButton, Qt::NoModifier, QPoint(150,350),100);

    // Add BOTS
    QPushButton *northButton = testSLob->findChild<QPushButton *>("north_b");
    QPushButton *southButton = testSLob->findChild<QPushButton *>("south_b");
    QPushButton *eastButton = testSLob->findChild<QPushButton *>("east_b");
    QPushButton *westButton = testSLob->findChild<QPushButton *>("west_b");
    QTest::qWait(500);
    QTest::mouseMove (eastButton, QPoint(20,20),-1);
    QTest::qWait(500);
    QTest::mouseClick (eastButton, Qt::LeftButton, Qt::NoModifier, QPoint(20,20),100);
    QTest::qWait(500);
    QTest::mouseMove (westButton, QPoint(20,20),-1);
    QTest::qWait(500);
    QTest::mouseClick (westButton, Qt::LeftButton, Qt::NoModifier, QPoint(20,20),100);
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(475,290),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLob->childAt(QPoint(475,290)), Qt::LeftButton, Qt::NoModifier, QPoint(475,290),100);
    //Send the names of the players and bots selected to server.
    QList<QVariant> sendPlayer = startGame->takeFirst();
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[0] == testSLob->findChild<QLabel *>("north")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[1] == testSLob->findChild<QLabel *>("south")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[2] == testSLob->findChild<QLabel *>("east")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[3] == testSLob->findChild<QLabel *>("west")->text());

    //Reset for next test
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(150,430),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLob->childAt(QPoint(150,430)), Qt::LeftButton, Qt::NoModifier, QPoint(150,430),100);
    QTest::qWait(500);
    emit playerJoined("Kai626 #LEDGEND");
    pJoined = addPlayerP->takeFirst();
    QVERIFY(qvariant_cast<QString>(pJoined.at(0)) == playerList->itemAt(10,35)->text());
    QTest::qWait(500);
    QTest::mouseMove (playerList->viewport(), QPoint(10,35),-1);
    QTest::qWait(500);
    QTest::mouseClick (playerList->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(10,35),100);
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(150,350),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLob->childAt(QPoint(150,350)), Qt::LeftButton, Qt::NoModifier, QPoint(150,350),100);
    QTest::qWait(500);
    QTest::mouseMove (southButton, QPoint(20,20),-1);
    QTest::qWait(500);
    QTest::mouseClick (southButton, Qt::LeftButton, Qt::NoModifier, QPoint(20,20),100);
    QTest::qWait(500);
    QTest::mouseMove (eastButton, QPoint(20,20),-1);
    QTest::qWait(500);
    QTest::mouseClick (eastButton, Qt::LeftButton, Qt::NoModifier, QPoint(20,20),100);
    QTest::qWait(500);
    QTest::mouseMove (playerList->viewport(), QPoint(10,10),-1);
    QTest::qWait(500);
    QTest::mouseClick (playerList->viewport(), Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(150,350),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLob->childAt(QPoint(150,350)), Qt::LeftButton, Qt::NoModifier, QPoint(150,350),100);
    QTest::qWait(500);
    QTest::qWait(500);
    QTest::mouseMove (testSLob, QPoint(475,290),-1);
    QTest::qWait(500);

    // Check if sent
    QTest::mouseClick (testSLob->childAt(QPoint(475,290)), Qt::LeftButton, Qt::NoModifier, QPoint(475,290),100);
    //Send the names of the players and bots selected to server.
    sendPlayer = startGame->takeFirst();
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[0] == testSLob->findChild<QLabel *>("north")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[1] == testSLob->findChild<QLabel *>("south")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[2] == testSLob->findChild<QLabel *>("east")->text());
    QVERIFY(qvariant_cast<QVector<QString>>(sendPlayer.at(0))[3] == testSLob->findChild<QLabel *>("west")->text());
    testSLob->close();


}
