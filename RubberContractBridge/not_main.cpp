// This main is solely used for testing

#include "unit-tests/testservernetwork.h"

int main(int argc, char *argv[])
{
//     Test the main class
    testServerNetwork testServerNet;
    QTest::qExec(&testServerNet);
}
