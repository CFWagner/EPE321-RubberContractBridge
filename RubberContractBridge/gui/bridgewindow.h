#ifndef BRIDGEWINDOW_H
#define BRIDGEWINDOW_H

#include "game-server/bid.h"
#include "bidcardsselected.h"
#include "game-server/playergamestate.h"
#include "playcardselected.h"
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <QDebug>

namespace Ui {
class bridgeWindow;
}

class bridgeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit bridgeWindow(QWidget *parent = nullptr);
    ~bridgeWindow();
    void setupWindow();
    void staticGUIElements();
    void setupHand();
public slots:
    void getUpdateGameState(PlayerGameState player);
    void getCardChosen(PlayCardSelected*);
private slots:
    void on_button_exit_clicked();

private:
    Ui::bridgeWindow *ui;
    PlayerGameState player;
    PlayCardSelected *cardsInHand[13];
    PlayCardSelected *cardMine;
    int count = 0;
};

#endif // BRIDGEWINDOW_H
