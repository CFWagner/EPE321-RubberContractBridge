#ifndef AI_H
#define AI_H
#include "game-server/player.h"
#include "enumerations/PlayerPosition.h"
#include "enumerations/Team.h"
#include "game-server/bid.h"
#include "game-server/card.h"
#include "game-server/playergamestate.h"


#include <QObject>

class AI : public Player
{
    Q_OBJECT
public:
    explicit AI(QObject *parent = nullptr);
    void notifyBidTurn();
    void notifyMoveTurn();
    void updateGameState(PlayerGameState gameState);
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    //Don't need message so won't implement?????
    void gameTerminated(QString reason);
    void message(QString source, QString message);
    //getters for testing
    CardSet getHand();
    Bid getBidContract();
    Bid getBidCurrent();
    //setters for testing
    void setCurrentBid(Bid bidding);
    void setContractBid(Bid contracter);
    void initialMainSet();
    Card guessMove();
    Bid guessBid();
    void initialBidSet();
    //move variables here now just for testing
    CardSet myhand;
    CardSet canPlay; //available legal cards to play if size = 0 then try to play trump or higher suit as top card
private:

    void generateAvailableCards();
    void removecards(CardSet handy);
    void removebids();
    void generatedeck();
    void generatebidlist();
    PlayerGameState currentState;
    CardSuit trump;
    CardSet dummyhand;
    CardSet currentTricks;
    Bid contract;
    Bid currentbid;
    PlayerPosition dummypos;
    CardSet dummyPlay;
    Card cardPlayed;
    CardSet deck;
    QVector<Bid> bidlist;




signals:

};

#endif // AI_H
