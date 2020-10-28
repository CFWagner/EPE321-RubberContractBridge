#ifndef TESTPLAYERNETWORK_H
#define TESTPLAYERNETWORK_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "network/servernetwork.h"
#include "network/clientnetwork.h"
#include "network/playernetwork.h"

class testPlayerNetwork : public QObject
{
    Q_OBJECT
public:
    explicit testPlayerNetwork(QObject *parent = nullptr);

private slots:
    // All private slots should be run in the following order, since they depend on each other.
    void verifyServerWorking();
    void addClients();
    void testStopListeningClientDisconnection();
    void disconnectClientFromServerAfterGameStarted();
    void testCommunicationsToClient();
    void testCommunicationsFromClient();
    void testRepetitiveCommunication();
    void testErrors();
    void cleanupTestCase();

signals:
    // Signals to connect to NetworkPlayer class
    void emitTxRequestLogin(QHostAddress serverIP, quint16 port, QString playerName, QString password);
    void emitTxBidSelected(Bid bid);
    void emitTxMoveSelected(Card card);
    void emitTxMessage(QString msg);

private:
    void addManyClients(int numberOfClients);
    void addPlayerNetwork(QString playerName, QTcpSocket** returnPlayerSocket = nullptr);
    void checkAllCientSignals();
    void checkAllPlayerSignals();
    void checkAllServerSignals();

    PlayerGameState generatePlayerGameState();
    Bid generateBid();
    Card generateCard();

    QString passwordServer;
    quint16 port;
    QHostAddress ip;
    QString playerName;
    QTcpSocket** testPlayerSocket;

    QVector<QString> playerNames;

    ServerNetwork testServerNetA;
    QVector<ClientNetwork*> testClientNet;
    QVector<PlayerNetwork*> testPlayerNet;

    QSignalSpy *spyServer;
    QSignalSpy *spyServerPlayerJoined;
    QSignalSpy *spyServerError;
    QSignalSpy *spyServerPlayerDisconnected;

    QVector<QSignalSpy*> spyClientConnectResult;
    QVector<QSignalSpy*> spyClientError;
    QVector<QSignalSpy*> spyClientLoginResult;
    QVector<QSignalSpy*> spyClientServerDisconnected;
    QVector<QSignalSpy*> spyClientGameTerminated;

    QVector<QSignalSpy*> spyClientNotifyBidTurn;
    QVector<QSignalSpy*> spyClientNotifyMoveTurn;
    QVector<QSignalSpy*> spyClientNotifyBidRejected;
    QVector<QSignalSpy*> spyClientNotifyMoveRejected;
    QVector<QSignalSpy*> spyClientUpdateGameState;
    QVector<QSignalSpy*> spyClientMessageReceived;

    QVector<QSignalSpy*> spyPlayerGeneralError;
    QVector<QSignalSpy*> spyPlayerBidSelected;
    QVector<QSignalSpy*> spyPlayerMoveSelected;
    QVector<QSignalSpy*> spyPlayerMessageGenerated;
    QVector<QSignalSpy*> spyPlayerClientDisconnected;
};

#endif // TESTPLAYERNETWORK_H
