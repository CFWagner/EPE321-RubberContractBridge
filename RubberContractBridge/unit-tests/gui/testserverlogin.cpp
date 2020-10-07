#include "testserverlogin.h"
TestServerLogin::TestServerLogin(QObject *parent) : QObject(parent)
{

}
TestServerLogin::~TestServerLogin()
{

}

void TestServerLogin::Login()
{
    testservergui.show();
    while (!testservergui.isVisible()) {
         QTest::qWait(200);
    }
    //Test Setup signal emits.
    //qRegisterMetaType<QHostAddress>();
    spyPassword = new QSignalSpy(&testservergui, SIGNAL(setPassword(QString)));
    spyAddress = new QSignalSpy(&testservergui, SIGNAL(sendServerDetails(QHostAddress, quint16)));
    QLineEdit *passwordL = testservergui.findChild<QLineEdit *>("passswordLine");
    QLineEdit *ipAddressL = testservergui.findChild<QLineEdit *>("ipLine");
    QLineEdit *portL = testservergui.findChild<QLineEdit *>("portLine");

    //Test 1 verify the signal exists.
    QVERIFY(spyPassword->isValid());
    QVERIFY(spyAddress->isValid());

    //Test 2 check valid password sent.
    passwordServer = "12345%^@";
    QTest::keyClicks(passwordL, passwordServer);
    testservergui.attemptLogin();
    QList<QVariant> argumentPassword = spyPassword->takeLast();
    QVERIFY(argumentPassword.at(0) == "12345%^@");
    QTest::qWait(2000);
    passwordL->clear();

    //Test 2 check invalid password sent.
    passwordServer = "12345";
    QTest::keyClicks(passwordL, passwordServer);
    testservergui.attemptLogin();
    argumentPassword = spyPassword->takeLast();
    QVERIFY(argumentPassword.at(0) == "INVALID");
    QTest::qWait(2000);
    passwordL->clear();

    //Test 3 check if Address and port is sent if specified.
    passwordServer = "12345%^@";
    port = 61074;
    ipAddress = QHostAddress::LocalHost;
    QTest::keyClicks(passwordL, passwordServer);
    QTest::keyClicks(ipAddressL, ipAddress.toString());
    QTest::keyClicks(portL,"61074");
    testservergui.attemptLogin();
    QList<QVariant> argumentAddress = spyAddress->takeFirst();
    //QVERIFY(qvariant_cast<QHostAddress>(argumentAddress.at(0)) == ipAddress);
    QVERIFY(argumentAddress.at(1) == port);
    QTest::qWait(2000);
    passwordL->clear();
    ipAddressL->clear();
    portL->clear();

    //Test 4 Check for default port and address.
    passwordServer = "12345%^@";
    QTest::keyClicks(passwordL, passwordServer);
    QTest::keyClicks(ipAddressL, "");
    QTest::keyClicks(portL,"");
    testservergui.attemptLogin();
    argumentAddress = spyAddress->takeLast();
    //QVERIFY(qvariant_cast<QHostAddress>(argumentAddress.at(0)) == QHostAddress::LocalHost);
    QVERIFY(argumentAddress.at(1) == 61074);
    testservergui.close();

}
