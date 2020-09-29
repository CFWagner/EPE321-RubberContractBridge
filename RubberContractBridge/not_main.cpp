// This main is solely used for testing

#include "unit-tests/testplayernetwork.h"
#include "unit-tests/testclientnetwork.h"

int main(int argc, char *argv[])
{
    // Test the main class
    testPlayerNetwork testPlayerNet;
    QTest::qExec(&testPlayerNet);
    
    testClientNetwork testClientNet;
    QTest::qExec(&testClientNet);
}
