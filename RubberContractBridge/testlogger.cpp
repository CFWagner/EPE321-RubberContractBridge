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
    QString context = "Input at context";
    QString msg = "Input at message";

    Logger testLog;
    QCOMPARE(testLog.isLogEnabled(), true);

    // Connect a signal to the slot in the Logger
    connect(this, &testLogger::emitLog , &testLog, &Logger::log);

    //Spy the return signal
    QSignalSpy spy(&testLog, &Logger::sendLog);
    QVERIFY(spy.isValid());

    emit emitLog(context,msg);

    QCOMPARE(spy.count(), 1); // make sure the signal was emitted exactly one time
    QList<QVariant> arguments = spy.takeFirst(); // take the first signal

    QVERIFY(arguments.at(0).type() == QVariant::String); // verify the first argument
    QVERIFY(arguments.at(0).toString() == context);

    QVERIFY(arguments.at(1).type() == QVariant::String); // verify the first argument
    QVERIFY(arguments.at(1).toString() == msg);

    // Prepare for next test
    spy.clear();

    // Verify that the disable function works
    // Disable
    testLog.disableLog();
    QCOMPARE(testLog.isLogEnabled(), false);

    emit emitLog(context,msg);

    QCOMPARE(spy.count(), 0); // make sure the signal was emitted exactly one time

    // Not needed here, but can be very usefull
    // QVERIFY(spy.wait(1000));

}
