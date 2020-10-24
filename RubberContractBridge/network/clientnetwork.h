#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QJsonObject>
#include <QHostAddress>

#include "game-server/playergamestate.h"
#include "game-server/bid.h"
#include "game-server/card.h"

class ClientNetwork : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetwork(QObject *parent = nullptr);
    ~ClientNetwork();

    // Unit test data
    QVector<bool> getUnitTest();

public slots:
    void txRequestLogin(QHostAddress serverIP, quint16 port, QString playerName, QString password);
    void txBidSelected(Bid bid);
    void txMoveSelected(Card card);
    void txMessage(QString msg);

private slots:
    void rxAll();
    void internalServerDisconnected(); // Notice the name change between this and the signal's name in the Group design doc.
    void socketConnected(); // Notice that this function is not in UML diagram.
    void socketError(QAbstractSocket::SocketError socError);

signals:
    void connectionResult(int status, QString errorMsg);
    // status = 0 :connection was successful
    // status = 1 :connection was not successful, since the IP address or/and port are invalid. (See note regarding errorMsg.)
    // status = 3 :already connected, old connection was kept. (Nothing was changed.)
    // errorMsg is empty except when status = 1, then the actual error will be displayed.
    // GUI is responsible for creating the messages regarding connection status. (genearl Info and warning signals will not be used for this.)

//    void serverNotFound(QString reason);
//    void generalInfo(QString infoMsg); // All information. (Should be displayed to the player.)
    void generalError(QString errorMsg); // All errors, except serverNotFound(). (Should be displayed to the player.)
    void notifyBidTurn();
    void notifyMoveTurn();
    void notifyBidRejected(QString reason);
    void notifyMoveRejected(QString reason);
    void loginResult(bool loginSuccessful, QString reason);
    void updateGameState(PlayerGameState gameState);
    void messageReceived(QString source, QString msg);
    //void serverDisconnected(); // Not used anymore, all terminations will happen through gameTerminated().
    // If client lost connection to the server, the reason given with gameTerminated will be: "Client lost connection to the server.")

    void gameTerminated(QString reason); // This can be emmited anytime after a game has been started.
    // When received it means that the connection to the server has been lost or the server terminated the game.
    // The Client (and probably the server) must be RESTARTED, before attempting to connect again.
    // The GUI is responsible for ensuring that the client is RESTARTED. (Do not go back to login page.)

private:
    void txAll(QJsonObject data);
    void rxNotifyBidTurn();
    void rxNotifyMoveTurn();
    void rxNotifyBidRejected(QJsonObject reasonObj);
    void rxNotifyMoveRejected(QJsonObject reasonObj);
    void rxLoginResult(QJsonObject resObj);
    void rxUpdateGameState(QJsonObject gsObj);
    void rxMessage(QJsonObject msgObj);
    void rxGameTerminated(QJsonObject reasonObj);
    void rxPingReceived();

    QString playerName;
    QString tempPlayerName;
    QString tempPassword;
    bool bLoggedIn;
    QTcpSocket* tcpSoc;
    QTimer* keepAlive;
    bool gameStarted;
    QDataStream in;
    qint64 idCounter;
    qint64 prevID;


    // Unit testing datastructures
    QVector<bool> bUnitTest;

};

#endif // CLIENTNETWORK_H
