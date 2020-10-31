#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMessageBox>
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

public slots:
    void updateGameState(PlayerGameState gameState);
    void gameTerminated(QString reason);
    void generalError(QString errorMsg);

private slots:
    void on_button_exit_clicked();

private:
    Ui::GameWindow *ui;
    ClientNetwork *clientNetwork = nullptr;
    PlayerGameState gameState;
};

#endif // GAMEWINDOW_H
