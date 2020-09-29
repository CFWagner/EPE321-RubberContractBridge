#include "testlogger.h"

testLogger::testLogger(QObject *parent) : QObject(parent)
{

}

void testLogger::testLogEnabled()
{
    Logger testLog;
    // Test default
    QCOMPARE(testLog.isLogEnabled(), true);
    // Disable
    testLog.disableLog();
    QCOMPARE(testLog.isLogEnabled(), false);
    // Enable
    testLog.enableLog();
    QCOMPARE(testLog.isLogEnabled(), true);
}

void testLogger::testLog()
{
    Logger testLog;
    QCOMPARE(testLog.isLogEnabled(), true);
}
