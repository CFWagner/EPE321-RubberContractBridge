#ifndef BIDWINDOW_H
#define BIDWINDOW_H

#include "game-server/bid.h"
#include "bidcardsselected.h"
#include "game-server/playergamestate.h"
#include <QHostAddress>
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <QDebug>

namespace Ui {
class BidWindow;
}

class BidWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BidWindow(QWidget *parent = nullptr);
    ~BidWindow();
    void setupWindow();
    void staticGUIElements();
    void setupBidTable();
    QVector<BidCardsSelected> getBidArray();
public slots:
    void getUpdateGameState(PlayerGameState player);
private slots:
    void on_button_exit_clicked();
private:
    Ui::BidWindow *ui;
    BidCardsSelected *bidCard;
    BidCardsSelected *bidCards[35];
    CardSuit suit;
    int bidAmount;
    PlayerPosition position;

    //Game state
    PlayerGameState player;

};

#endif // BIDWINDOW_H
