#ifndef SERVERLOBBY_H
#define SERVERLOBBY_H


#include <QWidget>
#include <QObject>
#include <QtWidgets>

namespace Ui {
class serverLobby;
}

class serverLobby : public QWidget
{
    Q_OBJECT

public:
    explicit serverLobby(QWidget *parent = nullptr);
    ~serverLobby();
    void windowSetup();
    void lobbyStart();
    void changeIcon(QString user);
    void removeSpot(int pos);
    QString playerlist[4] = {"","","",""};

public slots:
    //Player has disconnected and must be removed.
    void removePlayer (QString user);
    //Player has connectec and must be added.
    void addPlayer (QString user);

private slots:
    //clicked adds the AI opponents in the given slot.
    void on_south_clicked();

    void on_west_clicked();

    void on_east_clicked();

    void on_north_clicked();
    //clicked adds the player to the pool of player user.
    void on_addPlayer1_stateChanged(int arg1);

    void on_addPlayer2_stateChanged(int arg1);

    void on_addPlayer3_stateChanged(int arg1);

    void on_addPlayer4_stateChanged(int arg1);

    void on_addPlayer5_stateChanged(int arg1);

private:
    Ui::serverLobby *ui;
};

#endif // SERVERLOBBY_H
