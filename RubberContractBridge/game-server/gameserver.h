#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "player.h"
#include "servergamestate.h"
#include "enumerations/GameEvent.h"
#include <QObject>

// Class responsible for controlling the game at a high level and
// interfacing the players with the game logic and state
class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);
    ~GameServer();
    void addPlayer(Player* player);
    void initializeGame();
public slots:
    void gameEvent(GameEvent gameEvent);
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString message);
private:
    void broadcastStateUpdate(GameEvent gameEvent);
    Player* getPlayerInPosition(PlayerPosition position);
    Player* notifyNextPlayerTurn();
    ServerGameState* state = nullptr;
    QVector<Player*> players;
};

#endif // GAMESERVER_H
