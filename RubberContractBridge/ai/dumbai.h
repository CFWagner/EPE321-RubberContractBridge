#ifndef DUMBAI_H
#define DUMBAI_H

#include "game-server/player.h"
#include <QCoreApplication>
class DumbAI: public Player
{
    Q_OBJECT;
public:
    DumbAI(QObject *parent = nullptr);
    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState);
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void message(QString source, QString msg);
    void gameTerminated(QString reason);
private:
    PlayerGameState gameState;
    qint8 playCardPos = 0; // Keeps track of current position to attempt card play
};

#endif // DUMBAI_H
