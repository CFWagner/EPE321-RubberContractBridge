#include "testlogger.h"

int main(int argc, char *argv[])
{
    // Test the main class
    testLogger test1;
    QTest::qExec(&test1);
}
