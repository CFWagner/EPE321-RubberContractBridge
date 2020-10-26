#ifndef SERVERLOBBY_H
#define SERVERLOBBY_H

#include "game-server/server.h"
#include "hover.h"
#include <QAbstractItemView>
#include <QWidget>
#include <QLabel>
#include <QList>

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
public slots:
    void addPlayersLobby();
    void clearPlayersLobby();
    void startGameB();
    void addPlayer(QString name);
    void removePlayer(QString name);
signals:
    void playersSelected (QVector<QString> playerNames);
private slots:
    void on_north_b_clicked();

    void on_east_b_clicked();

    void on_west_b_clicked();

    void on_south_b_clicked();

private:
    Ui::ServerLobby *ui;
    int pageID = 2;
    int openSpots = 4;
    QVector<QString> playerNames = {"","","",""};
    int totalPlayers = 0;
    Server *serverCreated;
};

#endif // SERVERLOBBY_H
