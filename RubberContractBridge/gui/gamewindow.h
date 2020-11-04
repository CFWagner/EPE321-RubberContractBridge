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
#include "gui/scorewindow.h"


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
    void addCardToTrick();
    void indicatePlayerTurn();
    void setName(QString username);

public slots:
    void updateGameState(PlayerGameState gameState);
    void gameTerminated(QString reason);
    void generalError(QString errorMsg);
    void receiveBid(BidSelect *bidSelected);
    void receiveCard(CardSelected *card);
    void playerTurnBid();
    void playerTurnMove();
    void createHandTable();
    void createDummyHand();
    void bidRejected(QString reason);
    void moveRejected(QString reason);
    void setGameState(PlayerGameState gameState);
    QString getStyle(int);
    void updateTrickWon();
    void updateGeneralInfo();

signals:
    void bidAction(Bid bidMade);
    void cardAction(Card cardPlayed);
    void sendMessage(QString msg);
    void getScore(PlayerGameState gameState);

private slots:
    void on_button_exit_clicked();
    void messageReceived(QString source, QString msg);
    void keyPressEvent(QKeyEvent  *);
    void on_messagerB_clicked();
    void on_ScoreButon_clicked();

private:
    Ui::GameWindow *ui;
    ClientNetwork *clientNetwork = nullptr;
    PlayerGameState gameState;

    BidSelect *bidSelected = nullptr;
    BidSelect *bids = nullptr;
    BidSelect *bidTable [35];
    CardSelected *cardsInHand[13];
    CardSelected *dummyHandSet[13];
    CardSelected *cardMine;
    CardSelected *cardDummy;

    QLabel *bidBoard;
    QLabel *gameBoard;
    QLabel *turnIndicator;
    QLabel *trickPool[4];

    BidSelect *XX;
    BidSelect *X;
    BidSelect *passB;

    bool bidTableCreated = false;
    bool playerMayBid = false;
    bool playerMayPlay = false;
    bool cardsClickable = false;
    bool dummyCreate = true;
    QString name;
    int trickPos = 0;
    int trickPlacement = 0;
    ScoreWindow *scoreWindow = nullptr;
};

#endif // GAMEWINDOW_H
