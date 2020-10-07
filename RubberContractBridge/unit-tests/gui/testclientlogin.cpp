#include "testclientlogin.h"

testclientlogin::testclientlogin(QObject *parent) : QObject(parent)
{

}

testclientlogin::~testclientlogin()
{

}
void testclientlogin::Login()
{
    testLogin.show();
    while (!testLogin.isVisible()) {
         QTest::qWait(200);
    }
    //Test Setup signal emits.
    //qRegisterMetaType<QHostAddress>();
    spyLogin = new QSignalSpy(&testLogin, SIGNAL(connectToServer(QHostAddress ,quint16 , QString , QString )));
    QLineEdit *passwordL = testLogin.findChild<QLineEdit *>("passswordLines");
    QLineEdit *ipAddressL = testLogin.findChild<QLineEdit *>("ipAddressLine");
    QLineEdit *portL = testLogin.findChild<QLineEdit *>("portLine");
    QLineEdit *usernameL = testLogin.findChild<QLineEdit *>("userNameLine");
    //Test 1 verify the signal exists.
    QVERIFY(spyLogin->isValid());

    //Test 2 check invalid username sent.
    QTest::qWait(2000);
    username = "DOBOT";
    QTest::keyClicks(usernameL, username);
    testLogin.attemptLogin();
    QCOMPARE(username,"DOBOT");
    QTest::qWait(2000);
    usernameL->clear();

    //Test 2 check valid username.
    username = "Stitch";
    passwordServer = "";
    port = 61074;
    ipAddress = QHostAddress::LocalHost;
    QTest::keyClicks(ipAddressL, ipAddress.toString());
    QTest::keyClicks(portL, "61074");
    QTest::keyClicks(usernameL, username);
    QTest::keyClicks(passwordL, passwordServer);
    testLogin.attemptLogin();
    QList<QVariant> argumentLogin = spyLogin->takeFirst();
    QVERIFY(argumentLogin.at(1) == "61074");
    QVERIFY(argumentLogin.at(2) == passwordServer);
    QTest::qWait(2000);
    testLogin.close();

}
