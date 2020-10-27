#include "testgameserver.h"
#include "stubs/playerstub.h"

TestGameServer::TestGameServer(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of GameServer class instance
void TestGameServer::testGameServer()
{
    // Create players
    Player* player1 = new PlayerStub();
    Player* player2 = new PlayerStub();
    Player* player3 = new PlayerStub();
    Player* player4 = new PlayerStub();
    player1->setPlayerName("Player 1");
    player2->setPlayerName("Player 2");
    player3->setPlayerName("Player 3");
    player4->setPlayerName("Player 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer;

    // Add players to game server
    gameServer.addPlayer(player1);
    gameServer.addPlayer(player2);
    gameServer.addPlayer(player3);
    gameServer.addPlayer(player4);

    // Start game with game server
    gameServer.initializeGame();
}
