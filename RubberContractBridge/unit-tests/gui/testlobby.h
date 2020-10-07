#ifndef TESTLOBBY_H
#define TESTLOBBY_H
#include "gui/serverlobby.h"
#include <QtTest/QtTest>
#include <QHostAddress>
#include <QObject>

class testLobby : public QObject
{
    Q_OBJECT
public:
    explicit testLobby(QObject *parent = nullptr);

signals:
    void addPlayer(QString user);
    void removePlayer(QString user);
private:
private slots:
    void Lobby();
private:
    serverLobby testserlobby;
    QSignalSpy *spyaddPlayer;
    QSignalSpy *spyremovePlayer;
    QString username;
};

#endif // TESTLOBBY_H
