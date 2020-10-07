#ifndef SERVERGUI_H
#define SERVERGUI_H
#include "hover.h"
#include "serverlobby.h"
#include <QWidget>
#include <QObject>
#include <QtWidgets>
#include <QHostAddress>

namespace Ui {
class ServerGUI;
}

class ServerGUI : public QWidget
{
    Q_OBJECT

public:
    explicit ServerGUI(QWidget *parent = nullptr);
    ~ServerGUI();
    // Window is created such as the background and labels.
    void windowSetup();
    QPushButton *m_button;
    ServerGUI *servergui;
    // Attempt to create a connection between the GUI and network.
    void attemptLogin();
    // Checks if the password is strong enough.
    bool checkValidPassword();
public slots:
    // Button that initiates attempt login.
    void on_serverSetupButton_clicked();
    // Receives details on the success of the connection attempt and any errors if occured.
    void connectionResults(int status, QHostAddress ipAddress, quint16 port, QString errorMsg);
    // Receives general success of failure message.
    void generalInfo(QString infoMsg);
    void generalError(QString errorMsg);

signals:
    void setPassword(QString password);
    // Send all the server details to serverNetwork.
    void sendServerDetails(QHostAddress ipAddress, quint16 portID);

private:
    Ui::ServerGUI *ui;
    quint16 portID;
    QString password;
    QHostAddress ipAddress;
    quint16 defaultPort = 61074;
    serverLobby * lobbyWindow;
};

#endif // SERVERGUI_H
