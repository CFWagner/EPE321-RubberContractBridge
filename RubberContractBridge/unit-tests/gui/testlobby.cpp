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
    QTest::qWait(3000);
    emit addPlayer("Lydia");
    emit removePlayer("Stitch");
    QCheckBox *player2b = testserlobby.findChild<QCheckBox *>("addPlayer2");
    QTest::mouseClick(player2b, Qt::LeftButton);
    QLabel *player1l = testserlobby.findChild<QLabel *>("player1");
    QLabel *player2l = testserlobby.findChild<QLabel *>("player2");
    qDebug()<<player1l->text();
    QVERIFY(player2l->text() == "Lydia");
    QVERIFY(player1l->text() == "");
    QTest::qWait(3000);
    emit addPlayer("Kai");

}
