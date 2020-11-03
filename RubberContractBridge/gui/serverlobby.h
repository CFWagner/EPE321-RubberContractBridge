#ifndef SERVERLOBBY_H
#define SERVERLOBBY_H

#include "hover.h"
#include "loggerwindow.h"
#include <QAbstractItemView>
#include <QWidget>
#include <QLabel>
#include <QList>

namespace Ui {class ServerLobby;}

class ServerLobby : public QWidget
{
    Q_OBJECT

public:
    explicit ServerLobby(QWidget *parent = nullptr);
    ~ServerLobby();
    void setupWindow();
    void staticGUIElements();
    QVector<QString> getplayerNames();

public slots:
    //Add players to the lobby
    void addPlayersLobby();
    void clearPlayersLobby();
    //Attempt to start game.
    void startGameB();
    //players are added to the player pool.
    void addPlayer(QString name);
    //players are removed to the player pool.
    void removePlayer(QString name);
signals:
    void playersSelected (QVector<QString> playerNames);
    void closeServer();
    void rubberNumber(int rubberCount);
private slots:
    //Pool buttons to add BOTS.
    void on_north_b_clicked();
    void on_east_b_clicked();
    void on_west_b_clicked();
    void on_south_b_clicked();
    void keyPressEvent(QKeyEvent  *);

private:
    Ui::ServerLobby *ui;
    int pageID = 2;
    int openSpots = 4;
    QVector<QString> playerNames = {"","","",""};
    int totalPlayers = 0;
    LoggerWindow *loggerDisplay;
};

#endif // SERVERLOBBY_H
