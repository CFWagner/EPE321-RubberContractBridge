#include "testserver.h"
#include <QSignalSpy>

TestServer::TestServer(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of Server instance
void TestServer::testServer()
{
    // Initialise player name attributes for server initialisation
    QVector<QString> playerNames;
    playerNames.append("BOT1");
    playerNames.append("Matthew");
    playerNames.append("BOT2");
    playerNames.append("Chris");

    // Initialise connection attributes for server initialisation
    QHostAddress address = QHostAddress::LocalHost;
    quint16 port = 2143;
    QString password = "12345678!";

    // Instantiate Server
    Server server;

    // Initialise signal monitoring
    QSignalSpy spyConnectionResult(&server.getServerNetwork(), SIGNAL(connectionResult(int, QHostAddress, quint16, QString)));

    // Initialise general Server attributes
    server.setMaxRubbers(0);

    // Initialise Server connection and execute game with players
    server.serverPassword(password);
    server.serverIPAddressPort(address, port);

    // Wait for connection result from server
    while(spyConnectionResult.count() == 0);

    // Verify correct signals were emitted
    QList<QVariant> arguments = spyConnectionResult.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), 0);
    QCOMPARE(qvariant_cast<QHostAddress>(arguments.at(1)), address);
    QCOMPARE(arguments.at(2).toInt(), port);
    QCOMPARE(arguments.at(3), "");

    // Add selected 4 players to match and execute match with no rubbers
    server.playersSelected(playerNames);

    // Test for correct addition of players and instantiation of player objects
    const QVector<Player*> players = server.getGameServer().getPlayers();
    QCOMPARE(players.value(0)->getPlayerName(), "BOT1");
    QCOMPARE(players.value(0)->getPosition(), NORTH);
    QCOMPARE(players.value(1)->getPlayerName(), "Matthew");
    QCOMPARE(players.value(1)->getPosition(), SOUTH);
    QCOMPARE(players.value(2)->getPlayerName(), "BOT2");
    QCOMPARE(players.value(2)->getPosition(), EAST);
    QCOMPARE(players.value(3)->getPlayerName(), "Chris");
    QCOMPARE(players.value(3)->getPosition(), WEST);

    // Test correct value of Server attributes after playing no rubbers
    QCOMPARE(server.getMaxRubbers(), 0);
    QCOMPARE(server.getServerGameState().getPhase(), BIDDING);
    QCOMPARE(server.getServerGameState().getCurrentBid(), nullptr);
    QCOMPARE(server.getServerGameState().getContractBid(), nullptr);
    QCOMPARE(server.getServerGameState().getRubberNumber(), 1);
    QCOMPARE(server.getServerGameState().getGameNumber(), 1);
    QCOMPARE(server.getServerGameState().getDealNumber(), 0);
    QCOMPARE(server.getServerGameState().getTrickNumber(), 0);
    QCOMPARE(server.getServerGameState().getTricks().size(), 0);
    QCOMPARE(server.getServerGameState().getTeamVulnerable(N_S), false);
    QCOMPARE(server.getServerGameState().getTeamVulnerable(E_W), false);
    QCOMPARE(server.getServerGameState().getDealer(), NORTH);
    QCOMPARE(server.getServerGameState().getDeclarer(), NORTH);
    QCOMPARE(server.getServerGameState().getHandToPlay(), NORTH);
    QCOMPARE(server.getServerGameState().getPlayerTurn(), NORTH);
}
