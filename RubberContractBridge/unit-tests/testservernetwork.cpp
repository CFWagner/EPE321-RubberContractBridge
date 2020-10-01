#include "testservernetwork.h"

testServerNetwork::testServerNetwork(QObject *parent) : QObject(parent)
{

}

void testServerNetwork::initServer1()
{
    QString passwordServer = "abcdef1234$#@";
    QHostAddress ip = QHostAddress::LocalHost;
    ServerNetwork testServerNet;
    testServerNet.setPassword(passwordServer);
    testServerNet.initServer(ip);
    QVector<bool> bUnitTest = testServerNet.getUnitTest();

    // IP should be valid
    QVERIFY(bUnitTest[11] == false);

    // Server should be able to connect to port.
    QVERIFY(bUnitTest[12] == false);

    // The server is listening
    QVERIFY(bUnitTest[13] == true);

    // initServer not called twice
    QVERIFY(bUnitTest[10] == false);

    // Call ininServer a second time
    testServerNet.initServer(ip);
    bUnitTest = testServerNet.getUnitTest();

    // Should not try to connect
    QVERIFY(bUnitTest[10] == true);
    QVERIFY(bUnitTest[13] == false);

    testServerNet.deleteLater();

}

void testServerNetwork::initServer2()
{
    // Test invalid IP adress
    QString passwordServer = "abcdef1234$#@";
    QHostAddress ip = QHostAddress("192.168.56.10");
    ServerNetwork testServerNet;
    testServerNet.setPassword(passwordServer);
    testServerNet.initServer(ip);
    QVector<bool> bUnitTest = testServerNet.getUnitTest();

    // initServer not called twice
    QVERIFY(bUnitTest[10] == false);

    // IP should not be valid
    QVERIFY(bUnitTest[11] == true);

    // Server should be able to connect to port.
    QVERIFY(bUnitTest[12] == false);

    // The server is listening
    QVERIFY(bUnitTest[13] == true);

    testServerNet.deleteLater();

}
