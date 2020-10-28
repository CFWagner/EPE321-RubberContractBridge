#include "testclientlogin.h"

testClientLogin::testClientLogin(QObject *parent) : QObject(parent)
{

}

testClientLogin::~testClientLogin()
{
    connectClient->deleteLater();
    connectResult->deleteLater();
}

void testClientLogin::testClientLog()
{
    // Create instance of the entry window
    testCL = new ClientLogin();
    while (!testCL->isVisible()) {
        QTest::qWait(200); // Wait till the window is visable.
    }
    QTest::qWait(1000);
    QVERIFY(testCL->isVisible()); // Check if visable.

    //Signals check
    qRegisterMetaType<QHostAddress>();
    connectClient = new QSignalSpy(testCL, SIGNAL(connectToServer(QHostAddress, quint16, QString, QString)));
    connectResult = new QSignalSpy(this, SIGNAL(connectionResult(int,QString )));
    QVERIFY(connectClient->isValid());
    QVERIFY(connectResult->isValid());

    // Help function
    QPushButton *help = testCL->findChild<QPushButton *>("infoButton");
    QTest::qWait(500);
    QTest::mouseMove (help, QPoint(10,10),-1);
    QTest::qWait(500);
    QTest::mouseClick (help, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);

    //Enter details
    QLineEdit *usernameL = testCL->findChild<QLineEdit *>("usernameLine");
    QLineEdit *passwordL = testCL->findChild<QLineEdit *>("passwordLine");
    QLineEdit *ipAddressL = testCL->findChild<QLineEdit *>("ipAddressLine");
    QLineEdit *portL = testCL->findChild<QLineEdit *>("portLine");
    QTest::mouseMove (usernameL, QPoint(10,10),-1);
    QTest::qWait(500);
    QTest::mouseClick (usernameL, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QTest::keyClicks(usernameL, "BOT Kai");
    QTest::qWait(500);
    QTest::mouseMove (passwordL, QPoint(10,10),-1);
    QTest::qWait(500);
    QTest::mouseClick (passwordL, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QTest::keyClicks(passwordL, "12345^*&#@");
    QTest::qWait(500);
    QTest::mouseClick (ipAddressL, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QHostAddress ip = QHostAddress::LocalHost;
    QTest::keyClicks(ipAddressL, ip.toString());
    QTest::qWait(500);
    QTest::mouseClick (portL, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    QTest::qWait(500);
    QTest::keyClicks(portL, "61074");
    QTest::qWait(500);
    QTest::mouseMove (testCL, QPoint(180,360),-1);
    QTest::qWait(500);
    QTest::mouseClick (testCL->childAt(QPoint(180,360)), Qt::LeftButton, Qt::NoModifier, QPoint(180,360),100);
    QTest::qWait(500);
    QTest::mouseMove (usernameL, QPoint(10,10),-1);
    QTest::qWait(500);
    QTest::mouseClick (usernameL, Qt::LeftButton, Qt::NoModifier, QPoint(10,10),100);
    usernameL->clear();
    QTest::qWait(500);
    QTest::keyClicks(usernameL, "Kai 626");
    QTest::qWait(500);
    QTest::mouseMove (testCL, QPoint(180,360),-1);
    QTest::qWait(500);
    QTest::mouseClick (testCL->childAt(QPoint(180,360)), Qt::LeftButton, Qt::NoModifier, QPoint(180,360),100);

    // Check if the details are sent.
    QList<QVariant> details = connectClient->takeFirst();
    QVERIFY(qvariant_cast<QHostAddress>(details.at(0)) == testCL->getIPAddress());
    QVERIFY(qvariant_cast<quint16>(details.at(1)) == testCL->getPort());
    QVERIFY(qvariant_cast<QString>(details.at(2)) == testCL->getUserName());
    QVERIFY(qvariant_cast<QString>(details.at(3)) == testCL->getPassword());
    emit connectionResult(1, "Try another IP Address");
    QList<QVariant> connectDetails = connectResult->takeFirst();
    QVERIFY(qvariant_cast<int>(connectDetails.at(0)) == 1);
    connect(this,&testClientLogin::connectionResult,testCL,&ClientLogin::connectionResult);
    emit connectionResult(0, "Login successful");
    testCL->close();
}
