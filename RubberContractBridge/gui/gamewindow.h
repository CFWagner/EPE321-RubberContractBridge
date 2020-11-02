#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include "game-server/bid.h"
#include "bidselect.h"
#include "cardselected.h"
#include "network/clientnetwork.h"
#include "game-server/playergamestate.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(ClientNetwork *clientNetwork, QWidget *parent = nullptr);
    ~GameWindow();
    void setupWindow();
    void staticGUIElements();
    void createBidTable();
    void updateBidTable();
    void setName(QString username);
    void addCardToTrick();
    void indicatePlayerTurn();

public slots:
    void updateGameState(PlayerGameState gameState);
    void gameTerminated(QString reason);
    void generalError(QString errorMsg);
    void receiveBid(BidSelect *bidSelected);
    void receiveCard(CardSelected *card);
    void playerTurnBid();
    void createHandTable();
    void bidRejected(QString reason);
    void setGameState(PlayerGameState gameState);
    QString getStyle(int);

signals:
    void bidAction(Bid bidMade);
    void cardAction(Card cardPlayed);

private slots:
    void on_button_exit_clicked();

private:
    Ui::GameWindow *ui;
    ClientNetwork *clientNetwork = nullptr;
    PlayerGameState gameState;
    BidSelect *bidSelected = nullptr;
    BidSelect *bids = nullptr;
    BidSelect *bidTable [35];
    CardSelected *cardsInHand[13];
    QLabel *trickTabel[4];
    CardSelected *cardMine;
    QString name;
    bool playerMayBid = false;
    QLabel *turnIndicator;
    bool cardsClickable = false;
    int trickPos = 0;
    QLabel *bidBoard;
    QLabel *gameBoard;
    BidSelect *XX;
    BidSelect *X;
    BidSelect *passB;
    bool bidTableCreated = false;
};

#endif // GAMEWINDOW_H
