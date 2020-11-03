#ifndef TESTGAMESERVER_H
#define TESTGAMESERVER_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "game-server/gameserver.h"

class TestGameServer : public QObject
{
    Q_OBJECT
public:
    explicit TestGameServer(QObject *parent = nullptr);

private slots:
    void testGameServer();
    void testGameServerWithDumbAI();
    void testGameServerWithAI();
};

#endif // TESTGAMESERVER_H
