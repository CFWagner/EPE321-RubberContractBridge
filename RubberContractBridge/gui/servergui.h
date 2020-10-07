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
    void windowSetup();
    QPushButton *m_button;
    ServerGUI *servergui;
    void attemptLogin();
    bool checkValidPassword();
public slots:
    void on_serverSetupButton_clicked();
    void connectionResults(int status, QHostAddress ipAddress, quint16 port, QString errorMsg);
    void generalInfo(QString infoMsg);
    void generalError(QString errorMsg);

signals:
    void setPassword(QString password);
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
