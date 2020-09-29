#ifndef TESTPLAYERNETWORK_H
#define TESTPLAYERNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "network/playernetwork.h"

class testPlayerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testPlayerNetwork(QObject *parent = nullptr);

signals:

};

#endif // TESTPLAYERNETWORK_H
