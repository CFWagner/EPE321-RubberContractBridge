#ifndef TESTENTRYWINDOW_H
#define TESTENTRYWINDOW_H

#include "gui/entrywindow.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>

class testEntryWindow : public QObject
{
    Q_OBJECT
public:
    explicit testEntryWindow(QObject *parent = nullptr);
    ~testEntryWindow();
private slots:
    void testEntry();
signals:

private:
    EntryWindow *testEW;
    QSignalSpy *spyServerLogin;
    QSignalSpy *spyClientLogin;
};

#endif // TESTENTRYWINDOW_H
