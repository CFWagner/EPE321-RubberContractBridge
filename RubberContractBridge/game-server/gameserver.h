#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "player.h"
#include "servergamestate.h"
#include "enumerations/GameEvent.h"
#include <QObject>
#include <QCoreApplication>
#include <QEventLoop>

// Class responsible for controlling the game at a high level and
// interfacing the players with the game logic and state
class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = nullptr);
    ~GameServer();
    void addPlayer(Player* player);
    void executeMatch(qint32 maxRubbers, bool verboseOutput);
    const ServerGameState* getState() const;
    const QVector<Player*> getPlayers() const;
    void logScore();
    void logMatchWinner();
public slots:
    void gameEvent(GameEvent gameEvent);
    void bidSelected(Bid bid);
    void moveSelected(Card card);
    void messageGenerated(QString message);
    void setMatchCompleted(bool matchComplete);
signals:
    void logGenerated(QString context, QString msg);
private:
    QString getCardInfo(Card card);
    QString getBidInfo(Bid bid);
    void broadcastStateUpdate(GameEvent gameEvent);
    Player* getPlayerInPosition(PlayerPosition position);
    void notifyNextPlayerTurn();
    bool turnComplete;
    bool matchComplete;
    bool verboseOutput;
    ServerGameState* state = nullptr;
    QVector<Player*> players;
};

#endif // GAMESERVER_H
