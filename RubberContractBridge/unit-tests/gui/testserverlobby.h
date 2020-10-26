#ifndef TESTSERVERLOBBY_H
#define TESTSERVERLOBBY_H

#include "game-server/server.h"
#include "gui/serverlobby.h"
#include <QObject>
#include <QtTest/QtTest>

class testServerLobby : public QObject
{
    Q_OBJECT
public:
    explicit testServerLobby(QObject *parent = nullptr);
    ~testServerLobby();
private slots:
    void testSerLob();
signals:
    void playerJoined(QString playerName);
    void playerDisconnected(QString playerName);
private:
    ServerLobby *testSLob;
    Server *createServer;
    QSignalSpy *addPlayerP;
    QSignalSpy *removePlayerP;
    QSignalSpy *startGame;
};

#endif // TESTSERVERLOBBY_H
