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
private slots:
    void on_pushButton_5_clicked();

    void on_east_button_clicked();

    void on_north_button_clicked();

    void on_south_button_clicked();

    void on_west_button_clicked();

private:
    Ui::ServerLobby *ui;
    int pageID = 2;
    int openSpots = 4;
    QLabel *playersLabels [4];
};

#endif // SERVERLOBBY_H
