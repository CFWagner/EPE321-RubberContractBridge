#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "network/clientnetwork.h"

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

private:
    Ui::GameWindow *ui;
    ClientNetwork *clientNetwork = nullptr;
};

#endif // GAMEWINDOW_H
