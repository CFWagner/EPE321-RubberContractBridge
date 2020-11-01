#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMessageBox>
#include "game-server/bid.h"
#include "bidselect.h"
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

public slots:
    void updateGameState(PlayerGameState gameState);
    void gameTerminated(QString reason);
    void generalError(QString errorMsg);
    void receiveBid(BidSelect *bidSelected);
    void playerTurnBid();
    void bidRejected(QString reason);
    void setGameState(PlayerGameState gameState);

signals:
    void bidAction(Bid bidMade);

private slots:
    void on_button_exit_clicked();

private:
    Ui::GameWindow *ui;
    ClientNetwork *clientNetwork = nullptr;
    PlayerGameState gameState;
    BidSelect *bidSelected = nullptr;
    BidSelect *bids = nullptr;
    BidSelect *bidTable [35];
    QString name;
    bool playerMayBid = false;
};

#endif // GAMEWINDOW_H
