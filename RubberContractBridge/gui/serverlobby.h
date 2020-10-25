#ifndef SERVERLOBBY_H
#define SERVERLOBBY_H

#include <QWidget>

namespace Ui {
class ServerLobby;
}

class ServerLobby : public QWidget
{
    Q_OBJECT

public:
    explicit ServerLobby(QWidget *parent = nullptr);
    ~ServerLobby();

private:
    Ui::ServerLobby *ui;
};

#endif // SERVERLOBBY_H
