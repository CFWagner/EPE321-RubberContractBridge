// This main is solely used for testing
#include <QApplication>
#include "unit-tests/network/testservernetwork.h"
#include "unit-tests/network/testplayernetwork.h"
#include "unit-tests/network/testclientnetwork.h"

int main(int argc, char *argv[])
{
    // QApplication is nescessary so that QSignalSpy.wait() can be used in the tests.
    QApplication rcbApplication(argc, argv);

    // Test the main class
//    testServerNetwork testServerNet;
//    QTest::qExec(&testServerNet);

//    testClientNetwork testClientNet;
//    QTest::qExec(&testClientNet);

    testPlayerNetwork testPlayerNet;
    QTest::qExec(&testPlayerNet);

    return rcbApplication.exec();
}
