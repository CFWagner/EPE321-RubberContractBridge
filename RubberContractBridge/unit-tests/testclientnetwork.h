#ifndef TESTCLIENTNETWORK_H
#define TESTCLIENTNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "network/clientnetwork.h"

class testClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testClientNetwork(QObject *parent = nullptr);

private slots:
    void Login();

signals:

};

#endif // TESTCLIENTNETWORK_H
