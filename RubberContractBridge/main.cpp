// This main is solely used for testing

#include "unit-tests/testclientnetwork.h"


int main(int argc, char *argv[])
{
    // Test the main class
    testClientNetwork test1;
    QTest::qExec(&test1);
}
