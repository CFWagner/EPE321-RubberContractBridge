#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include "game-server/playergamestate.h"
#include "network/clientnetwork.h"
#include "gui/gamewindow.h"
#include "hover.h"
#include "gui/gamewindow.h"
#include <QHostAddress>
#include <QWidget>
#include <QObject>

namespace Ui {class ClientLogin;}

class ClientLogin : public QWidget
{
    Q_OBJECT

public:
    explicit ClientLogin(QWidget *parent = nullptr);
    ~ClientLogin();
    void setupWindow();
    void staticGUIElements();

public slots:
    void attemptLoginButton();
    void loginStatus(bool loginSuccessful, QString reason);
    void connectionResult(int status, QString errorMsg);
    void serverDisconnected();
    void generalError(QString errorMsg);
    void updateGameState(PlayerGameState gameState);

signals:
    void connectToServer(QHostAddress serverIP, quint16 port, QString playerName, QString password);

private slots:
    void on_infoButton_clicked();

private:
    Ui::ClientLogin *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    QString username;
    int pageID = 3;
    bool loginSuccessful = false;
    ClientNetwork *networkConnection = nullptr;
    GameWindow *playerWindow = nullptr;
};

#endif // CLIENTLOGIN_H
