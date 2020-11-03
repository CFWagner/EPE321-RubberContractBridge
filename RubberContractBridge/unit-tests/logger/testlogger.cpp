#include "testlogger.h"

/**
 * Constructor
 * @param parent
 */

testLogger::testLogger(QObject *parent) : QObject(parent)
{
    // Empty
}

/**
 * Test getters and setters of the Logger class.
 * Test the log enable and disable functions.
 * Test the isLogEnabled functions.
 */

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

/**
 * Test the logger class' signal and slot.
 * Informally verify that the output printed to the terminal is
 * as shown at the end of this function.
 */

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

    QVERIFY(arguments.at(0).type() == QVariant::String);

    QVERIFY(arguments.at(1).type() == QVariant::String); // verify the first argument
    QVERIFY(arguments.at(1).toString() == context);

    QVERIFY(arguments.at(2).type() == QVariant::String); // verify the first argument
    QVERIFY(arguments.at(2).toString() == msg);

    // Prepare for next test
    spy.clear();

    // Verify that the disable function works
    // Disable
    testLog.disableLog();
    QCOMPARE(testLog.isLogEnabled(), false);

    emit emitLog(context,msg);

    QCOMPARE(spy.count(), 0); // Make sure the signal was emitted exactly one time

    // Enable the log again
    testLog.enableLog();

    for (int i = 1; i < 5; i++) emit emitLog("Func " + QString::number(i), "Context " + QString::number(i*2));

    // Informally verify that the following was printed to the command line.
    // The date and time should be the current data and time.
    // The current data and time in this case was: 2020/10/28 02:45 (yyyy/mm/dd hh:mm)
    /*
    2020/10/28 02:45 {Input at context}: Input at message
    2020/10/28 02:45 {Func 1}: Context 2
    2020/10/28 02:45 {Func 2}: Context 4
    2020/10/28 02:45 {Func 3}: Context 6
    2020/10/28 02:45 {Func 4}: Context 8
    */
}
