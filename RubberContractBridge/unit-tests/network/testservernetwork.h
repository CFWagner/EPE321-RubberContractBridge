#ifndef TESTSERVERNETWORK_H
#define TESTSERVERNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "network/servernetwork.h"


class testServerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testServerNetwork(QObject *parent = nullptr);

private slots:
    void initServer1();
    void initServer2();
signals:

};

#endif // TESTSERVERNETWORK_H
