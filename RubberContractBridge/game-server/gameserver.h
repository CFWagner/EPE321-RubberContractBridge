#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "player.h"
#include "servergamestate.h"
#include "enumerations/GameEvent.h"
#include <QObject>

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);
public slots:
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString message);
signals:
    void gameEvent(GameEvent event);
private:
    ServerGameState state;
    QVector<Player*> players;
};

#endif // GAMESERVER_H
