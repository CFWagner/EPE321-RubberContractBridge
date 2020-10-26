#include "testentrywindow.h"

testEntryWindow::testEntryWindow(QObject *parent) : QObject(parent)
{

}

testEntryWindow::~testEntryWindow()
{
    spyServerLogin->deleteLater();
    spyClientLogin->deleteLater();
}

void testEntryWindow::testEntry()
{
    // Create instance of the entry window
    testEW = new EntryWindow();
    while (!testEW->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);
    QVERIFY(testEW->isVisible()); // Check if visable.

    // Check signals
    Hover *serverBut = testEW->findChild<Hover *>("Server Button");
    Hover *clientBut = testEW->findChild<Hover *>("Client Button");
    spyServerLogin = new QSignalSpy(serverBut,SIGNAL(gotoServerLogin()));
    spyClientLogin = new QSignalSpy(clientBut,SIGNAL(gotoClientLogin()));
    QVERIFY(spyServerLogin->isValid()); // Check if valid signal.
    QVERIFY(spyClientLogin->isValid()); // Check if valid signal.

    //Simulate
    QTest::mouseMove (testEW, QPoint( 90, 330 ),-1);
    QTest::qWait(500);
    QTest::mouseMove (testEW, QPoint( 450, 330 ),-1);
    QTest::qWait(500);
    QTest::mouseMove (testEW, QPoint( 120, 330 ),-1);
    QTest::qWait(500);
    QTest::mouseClick (serverBut, Qt::LeftButton, Qt::NoModifier, QPoint( 120, 330 ), 100);

    //Check if server is entered.
    QVERIFY(testEW->getPageID() == 0);
    testEW->serverLogin->close();
}
