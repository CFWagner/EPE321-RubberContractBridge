// This main is solely used for testing

#include "unit-tests/network/testservernetwork.h"
#include "unit-tests/network/testplayernetwork.h"
#include "unit-tests/network/testclientnetwork.h"

int main(int argc, char *argv[])
{
//     Test the main class
    testServerNetwork testServerNet;
    QTest::qExec(&testServerNet);
    
    testPlayerNetwork testPlayerNet;
    QTest::qExec(&testPlayerNet);
    
    testClientNetwork testClientNet;
    QTest::qExec(&testClientNet);
}
