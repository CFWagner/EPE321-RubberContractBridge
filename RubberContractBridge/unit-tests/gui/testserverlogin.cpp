#include "testserverlogin.h"

testServerLogin::testServerLogin(QObject *parent) : QObject(parent)
{

}

testServerLogin::~testServerLogin()
{

}

void testServerLogin::testSerLog()
{
    // Create instance of the entry window
    testSLog = new ServerLogin();
    createServer = new Server();
    connect(testSLog,&ServerLogin::serverPassword,createServer,&Server::serverPassword);
    connect(testSLog,&ServerLogin::serverIPAddressPort,createServer,&Server::serverIPAddressPort);
    while (!testSLog->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);
    QVERIFY(testSLog->isVisible()); // Check if visable.

    //Signals check
    qRegisterMetaType<QHostAddress>();
    passwordSent = new QSignalSpy(testSLog, SIGNAL(serverPassword(QString)));
    addressSent = new QSignalSpy(testSLog, SIGNAL(serverIPAddressPort (QHostAddress,quint16)));
    QVERIFY(passwordSent->isValid());
    QVERIFY(addressSent->isValid());

    //Simulate server creation.
    QTest::mouseMove (testSLog, QPoint(150,170),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLog->childAt(QPoint( 150, 170 )), Qt::LeftButton, Qt::NoModifier, QPoint(150,170),100);
    QTest::qWait(500);
    QTest::keyClicks(testSLog->childAt(QPoint( 150, 170 )), "DumbPassword");
    QTest::qWait(500);
    QTest::mouseMove (testSLog, QPoint(150,350),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLog->childAt(QPoint(150,350)), Qt::LeftButton, Qt::NoModifier, QPoint(150, 350), 100);
    QTest::qWait(500);

    //Message appears that says the password is to weak.
    QTest::mouseMove (testSLog, QPoint( 150, 170 ),-1);
    QTest::qWait(500);
    QLineEdit *passwordL = testSLog->findChild<QLineEdit *>("passswordLine");
    passwordL->clear();
    QTest::qWait(500);
    QTest::mouseClick (testSLog->childAt(QPoint(150,170)), Qt::LeftButton, Qt::NoModifier, QPoint(150,170), 100);
    QTest::keyClicks(testSLog->childAt(QPoint(150, 170)), "12345^&#$");
    QTest::qWait(500);
    QTest::mouseMove (testSLog, QPoint(150,230),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLog->childAt(QPoint( 150, 230 )), Qt::LeftButton, Qt::NoModifier, QPoint( 150, 230 ), 100);
    QTest::qWait(500);
    QHostAddress ip = QHostAddress::LocalHost;
    QTest::keyClicks(testSLog->childAt(QPoint( 150, 230 )), ip.toString());
    QTest::qWait(500);
    QTest::mouseMove (testSLog, QPoint(150,280),-1);
    QTest::qWait(500);
    QTest::mouseClick (testSLog->childAt(QPoint(150,280)), Qt::LeftButton, Qt::NoModifier, QPoint(150,280), 100);
    QTest::qWait(500);
    QTest::keyClicks(testSLog->childAt(QPoint(150,280)),"61074");
    QTest::qWait(500);
    QTest::mouseMove (testSLog, QPoint( 150, 350 ),-1);
    QTest::mouseClick (testSLog->childAt(QPoint(150,350)), Qt::LeftButton, Qt::NoModifier, QPoint(150,350), 100);

    // Go to Server Lobby but first check what is sent over signal.
    QList<QVariant> argumentPassword = passwordSent->takeFirst();
    QVERIFY(qvariant_cast<QString>(argumentPassword.at(0)) == testSLog->getPassword());
    QList<QVariant> argumentAddress = addressSent->takeFirst();
    QVERIFY(qvariant_cast<QHostAddress>(argumentAddress.at(0)) == testSLog->getIPAddress());
    QVERIFY(qvariant_cast<quint16>(argumentAddress.at(1)) == testSLog->getPort());
}
