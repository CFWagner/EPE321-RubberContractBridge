// This main is solely used for testing

#include "unit-tests/testclientnetwork.h"

int main(int argc, char *argv[])
{
    // Test the main class
    testClientNetwork testClientNet;
    QTest::qExec(&testClientNet);
}
