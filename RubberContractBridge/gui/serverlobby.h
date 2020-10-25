#ifndef SERVERLOBBY_H
#define SERVERLOBBY_H

#include <QWidget>
#include "game-server/server.h"
namespace Ui {
class ServerLobby;
}

class ServerLobby : public QWidget
{
    Q_OBJECT

public:
    explicit ServerLobby(Server *serverCreated, QWidget *parent = nullptr);
    ~ServerLobby();
    void setupWindow();
    void staticGUIElements();

private:
    Ui::ServerLobby *ui;
};

#endif // SERVERLOBBY_H
