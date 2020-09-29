// This main is solely used for testing

#include "unit-tests/testservernetwork.h"
#include "unit-tests/testplayernetwork.h"
#include "unit-tests/testclientnetwork.h"

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
