#include "testservernetwork.h"

testServerNetwork::testServerNetwork(QObject *parent) : QObject(parent)
{

}

void testServerNetwork::initServer1()
{
    QString passwordServer = "abcdef1234$#@";
    qint16 port = 61074;
    QHostAddress ip = QHostAddress::LocalHost;
    ServerNetwork testServerNet1;
    testServerNet1.setPassword(passwordServer);

    // Monitor the connectionResult signal
    qRegisterMetaType<QHostAddress>();
    QSignalSpy spy1(&testServerNet1, SIGNAL(connectionResult(int,QHostAddress,qint16,QString)));
    QVERIFY(spy1.isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spy1.takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Try to init the server again
    testServerNet1.initServer(ip,port);

    arguments = spy1.takeFirst();
    QVERIFY(arguments.at(0) == 3);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    // Try to connect with an invalid port (IP and port already bounded to this application
    // (testServer1 is still using that port)
    ServerNetwork testServerNet2;
    testServerNet2.setPassword(passwordServer);

    // Monitor the connectionResult signal
    QSignalSpy spy2(&testServerNet2, SIGNAL(connectionResult(int,QHostAddress,qint16,QString)));
    QVERIFY(spy2.isValid());

    testServerNet2.initServer(ip,port);

    arguments = spy2.takeFirst();
    QVERIFY(arguments.at(0) == 2);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "The bound address is already in use");

    // Connecting with same ip on a different port: should work.
    port = 61070;
    testServerNet2.initServer(ip,port);

    arguments = spy2.takeFirst();
    QVERIFY(arguments.at(0) == 0);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

    testServerNet1.deleteLater();
    testServerNet2.deleteLater();

}

void testServerNetwork::initServer2()
{
    // Test invalid IP adress
    QString passwordServer = "abcdef1234$#@";
    qint16 port = 61074;
    QHostAddress ip = QHostAddress("192.168.56.10");
    ServerNetwork testServerNet1;
    testServerNet1.setPassword(passwordServer);

    // Monitor the connectionResult signal
    qRegisterMetaType<QHostAddress>();
    QSignalSpy spy1(&testServerNet1, SIGNAL(connectionResult(int,QHostAddress,qint16,QString)));
    QVERIFY(spy1.isValid());

    // Server should be able to connect to port.
    testServerNet1.initServer(ip,port);

    QList<QVariant> arguments = spy1.takeFirst();
    QVERIFY(arguments.at(0) == 1);
    QVERIFY(qvariant_cast<QHostAddress>(arguments.at(1)) == ip);
    QVERIFY(arguments.at(2) == port);
    QVERIFY(arguments.at(3) == "");

   testServerNet1.deleteLater();
}
