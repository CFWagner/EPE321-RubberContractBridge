#ifndef PLAYERSTUB_H
#define PLAYERSTUB_H

#include "game-server/player.h":

class PlayerStub: public Player
{
public:
    PlayerStub(QObject *parent = nullptr);
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

#endif // PLAYERSTUB_H


//signals:
//void bidSelected(Bid bid);
//void moveSelected(Card card);
//void messageGenerated(QString message);
