#include "unit-tests/ai/testai.h"
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    // Test the main class
    testai test1;
    qDebug() << "Starting";
    QTest::qExec(&test1);
}
