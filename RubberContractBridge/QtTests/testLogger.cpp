#include <QtTest/QtTest>
#include "logger.h"

class testLogger: public QObject
{
    Q_OBJECT
private slots:
    void testLogEnabled();
    void testLog();
};

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

//QTEST_MAIN(testLogger)
//#include "testlogger.moc"
