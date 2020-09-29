#include "testservernetwork.h"

testServerNetwork::testServerNetwork(QObject *parent) : QObject(parent)
{

}

void testServerNetwork::initServer()
{
    QString passwordServer = "abcdef1234$#@";
    QHostAddress ip = QHostAddress::LocalHost;
    ServerNetwork testServerNet;
    testServerNet.setPassword(passwordServer);
    testServerNet.initServer(ip);
    testServerNet.deleteLater();

    ip = "192.168.56.1";
    ServerNetwork testServerNet2;
    testServerNet2.setPassword(passwordServer);
    testServerNet2.initServer(ip);
    testServerNet2.deleteLater();

    ip = "192.168.56.10";
    ServerNetwork testServerNet3;
    testServerNet3.setPassword(passwordServer);
    testServerNet3.initServer(ip);
    testServerNet3.deleteLater();


}
