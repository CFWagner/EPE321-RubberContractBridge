#ifndef TESTLOGGER_H
#define TESTLOGGER_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "logger/logger.h"

class testLogger : public QObject
{
    Q_OBJECT
public:
    explicit testLogger(QObject *parent = nullptr);

private slots:
    void testLogEnabled();
    void testLog();

signals:
    void emitLog(QString context, QString msg);
};

#endif // TESTLOGGER_H
