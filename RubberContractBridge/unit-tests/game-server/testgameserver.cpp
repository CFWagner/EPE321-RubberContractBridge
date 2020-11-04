#include "testgameserver.h"
#include "stubs/playerstub.h"
#include "ai/ai.h"
#include "ai/dumbai.h"

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
    GameServer gameServer1;

    // Add players to game server
    gameServer1.addPlayer(player1);
    gameServer1.addPlayer(player2);
    gameServer1.addPlayer(player3);
    gameServer1.addPlayer(player4);

    // Start game with game server
    qint8 maxRubbers = 1;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);

    // Create players
    player1 = new PlayerStub();
    player2 = new PlayerStub();
    player3 = new PlayerStub();
    player4 = new PlayerStub();
    player1->setPlayerName("Player 1");
    player2->setPlayerName("Player 2");
    player3->setPlayerName("Player 3");
    player4->setPlayerName("Player 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer2;

    // Add players to game server
    gameServer2.addPlayer(player1);
    gameServer2.addPlayer(player2);
    gameServer2.addPlayer(player3);
    gameServer2.addPlayer(player4);

    // Start game with game server
    maxRubbers = 5;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);
}

// Test for correct construction and operation of GameServer class instance
void TestGameServer::testGameServerWithDumbAI()
{
    // Create players
    Player* player1 = new DumbAI();
    Player* player2 = new DumbAI();
    Player* player3 = new DumbAI();
    Player* player4 = new DumbAI();
    player1->setPlayerName("Bot 1");
    player2->setPlayerName("Bot 2");
    player3->setPlayerName("Bot 3");
    player4->setPlayerName("Bot 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer1;

    // Add players to game server
    gameServer1.addPlayer(player1);
    gameServer1.addPlayer(player2);
    gameServer1.addPlayer(player3);
    gameServer1.addPlayer(player4);

    // Start game with game server
    qint8 maxRubbers = 1;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);

    // Create players
    player1 = new DumbAI();
    player2 = new DumbAI();
    player3 = new DumbAI();
    player4 = new DumbAI();
    player1->setPlayerName("Bot 1");
    player2->setPlayerName("Bot 2");
    player3->setPlayerName("Bot 3");
    player4->setPlayerName("Bot 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer2;

    // Add players to game server
    gameServer2.addPlayer(player1);
    gameServer2.addPlayer(player2);
    gameServer2.addPlayer(player3);
    gameServer2.addPlayer(player4);

    // Start game with game server
    maxRubbers = 5;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);
}

// Test for correct construction and operation of GameServer class instance
void TestGameServer::testGameServerWithAI()
{
    // Create players
    Player* player1 = new AI();
    Player* player2 = new AI();
    Player* player3 = new AI();
    Player* player4 = new AI();
    player1->setPlayerName("Bot 1");
    player2->setPlayerName("Bot 2");
    player3->setPlayerName("Bot 3");
    player4->setPlayerName("Bot 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer1;

    // Add players to game server
    gameServer1.addPlayer(player1);
    gameServer1.addPlayer(player2);
    gameServer1.addPlayer(player3);
    gameServer1.addPlayer(player4);

    // Start game with game server
    qint8 maxRubbers = 1;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);

    // Create players
    player1 = new AI();
    player2 = new AI();
    player3 = new AI();
    player4 = new AI();
    player1->setPlayerName("Bot 1");
    player2->setPlayerName("Bot 2");
    player3->setPlayerName("Bot 3");
    player4->setPlayerName("Bot 4");
    player1->setPosition(NORTH);
    player2->setPosition(EAST);
    player3->setPosition(SOUTH);
    player4->setPosition(WEST);

    // Instantiate GameServer
    GameServer gameServer2;

    // Add players to game server
    gameServer2.addPlayer(player1);
    gameServer2.addPlayer(player2);
    gameServer2.addPlayer(player3);
    gameServer2.addPlayer(player4);

    // Start game with game server
    maxRubbers = 10;
    gameServer1.executeMatch(maxRubbers, false);
    QCOMPARE(gameServer1.getState()->getRubberNumber(), maxRubbers);
}
