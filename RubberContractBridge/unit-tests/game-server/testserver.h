#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "game-server/server.h"

class TestServer : public QObject
{
    Q_OBJECT
public:
    explicit TestServer(QObject *parent = nullptr);

private slots:
    void testServer();

};

#endif // TESTSERVER_H
