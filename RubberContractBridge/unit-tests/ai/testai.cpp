#include "testai.h"
#include <QtTest/QtTest>

testai::testai(QObject *parent) : QObject(parent)
{
}


void testai::testDeckGenerate()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
