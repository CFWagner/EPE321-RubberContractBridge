#include "testservergamestate.h"
#include "game-server/servergamestate.h"
#include <QSet>

// Default constructor
TestServerGameState::TestServerGameState(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of ServerGameState class instance
void TestServerGameState::testServerGameState()
{
    // Instantiate ServerGameState
    ServerGameState serverState;

    // Initialise singal monitoring
    qRegisterMetaType<GameEvent>("GameEvent");
    QSignalSpy spyGameEvent(&serverState, SIGNAL(gameEvent(GameEvent)));

    // Verify correct instantiation of attributes
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 0);
    QCOMPARE(serverState.getTrickNumber(), 0);
    QCOMPARE(serverState.getTricks().size(), 0);
    QCOMPARE(serverState.getTeamVulnerable(N_S), false);
    QCOMPARE(serverState.getTeamVulnerable(E_W), false);
    QCOMPARE(serverState.getDealer(), NORTH);
    QCOMPARE(serverState.getDeclarer(), NORTH);
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getDeck().getCardCount(), 52);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);

    // Check that the deck does not contain any duplicate cards
    QVector<Card> deckCardList;
    for(qint8 index = 0; index < serverState.getDeck().getCardCount(); ++ index){
        const Card &card = serverState.getDeck().getCard(index);
        QCOMPARE(deckCardList.contains(card), false);
        deckCardList.append(card);
    }

    // Test deal initiation
    serverState.startMatch(1);
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getTrickNumber(), 0);
    QCOMPARE(serverState.getTricks().size(), 0);
    QCOMPARE(serverState.getDealer(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);

    // Verify correct signals were emitted
    QCOMPARE(spyGameEvent.count(), 1);
    QList<QVariant> arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == BID_START);

    // Test bid validation when no valid bids have been made
    QCOMPARE(serverState.isBidValid(Bid(NORTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DOUBLE_BID)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, REDOUBLE_BID)), false);

    // Make four passes during the bidding phase when no bid has been made and test attributes
    serverState.updateBidState(Bid(NORTH, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    serverState.updateBidState(Bid(EAST, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), SOUTH);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    serverState.updateBidState(Bid(SOUTH, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    serverState.updateBidState(Bid(WEST, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(serverState.getDealer(), EAST);
    QCOMPARE(spyGameEvent.count(), 2);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == BID_RESTART);

    // Test attributes after making a valid bid that isn't a pass
    Bid bid1(EAST, DIAMONDS, 2);
    serverState.updateBidState(bid1);
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder() == bid1.getBidder(), true);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), SOUTH);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    // Test bid validation when one valid bid has been made
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DOUBLE_BID)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, REDOUBLE_BID)), false);

    // Test attributes after making a valid double bid
    serverState.updateBidState(Bid(SOUTH, DOUBLE_BID));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid()->getCall(), DOUBLE_BID);
    QCOMPARE(serverState.getCurrentBid()->getTrumpSuit(), DIAMONDS);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), EAST);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    // Test bid validation when one valid double bid has been made
    QCOMPARE(serverState.isBidValid(Bid(WEST, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DOUBLE_BID)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, REDOUBLE_BID)), true);

    // Test attributes after making a valid redouble bid
    serverState.updateBidState(Bid(WEST, REDOUBLE_BID));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid()->getCall(), REDOUBLE_BID);
    QCOMPARE(serverState.getCurrentBid()->getTrumpSuit(), DIAMONDS);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), EAST);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    // Test bid validation when one valid redouble bid has been made
    QCOMPARE(serverState.isBidValid(Bid(NORTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DOUBLE_BID)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, REDOUBLE_BID)), false);

    // Test attributes after making a valid bid update
    bid1 = Bid(NORTH, CLUBS, 3);
    serverState.updateBidState(bid1);
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), bid1.getBidder());
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    // Test attributes after 2 passes with a valid current bid
    serverState.updateBidState(Bid(EAST, PASS));
    serverState.updateBidState(Bid(SOUTH, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), bid1.getBidder());
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(spyGameEvent.count(), 2);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);

    // Test attributes after 3 passes with a valid current bid
    serverState.updateBidState(Bid(WEST, PASS));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(*serverState.getContractBid() == bid1, true);
    QCOMPARE(serverState.getContractBid()->getBidder(), bid1.getBidder());
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 1);
    QCOMPARE(serverState.getTricks().size(), 1);
    QCOMPARE(serverState.getTricks().value(1).getCardCount(), 0);
    QCOMPARE(serverState.getDeclarer(), bid1.getBidder());
    QCOMPARE(serverState.getDummy(), SOUTH);
    QCOMPARE(serverState.getHandToPlay(), EAST);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(spyGameEvent.count(), 4);
    QCOMPARE(serverState.getLastCardPlayed(), nullptr);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_BID);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == BID_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAY_START);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Manually assign player hands
    CardSet northHand;
    CardSet eastHand;
    CardSet southHand;
    CardSet westHand;

    northHand.addCard(Card(CLUBS, ACE));
    northHand.addCard(Card(CLUBS, TWO));
    northHand.addCard(Card(CLUBS, THREE));
    northHand.addCard(Card(DIAMONDS, FIVE));
    northHand.addCard(Card(HEARTS, NINE));
    northHand.addCard(Card(SPADES, SEVEN));
    northHand.addCard(Card(SPADES, KING));
    northHand.addCard(Card(HEARTS, FIVE));
    northHand.addCard(Card(CLUBS, SIX));
    northHand.addCard(Card(CLUBS, FIVE));
    northHand.addCard(Card(DIAMONDS, NINE));
    northHand.addCard(Card(DIAMONDS, QUEEN));
    northHand.addCard(Card(SPADES, NINE));

    eastHand.addCard(Card(DIAMONDS, ACE));
    eastHand.addCard(Card(HEARTS, TWO));
    eastHand.addCard(Card(DIAMONDS, THREE));
    eastHand.addCard(Card(CLUBS, QUEEN));
    eastHand.addCard(Card(CLUBS, TEN));
    eastHand.addCard(Card(CLUBS, NINE));
    eastHand.addCard(Card(CLUBS, FOUR));
    eastHand.addCard(Card(DIAMONDS, TEN));
    eastHand.addCard(Card(DIAMONDS, EIGHT));
    eastHand.addCard(Card(DIAMONDS, SEVEN));
    eastHand.addCard(Card(HEARTS, KING));
    eastHand.addCard(Card(HEARTS, JACK));
    eastHand.addCard(Card(HEARTS, SEVEN));

    southHand.addCard(Card(DIAMONDS, TWO));
    southHand.addCard(Card(HEARTS, ACE));
    southHand.addCard(Card(HEARTS, THREE));
    southHand.addCard(Card(DIAMONDS, FOUR));
    southHand.addCard(Card(DIAMONDS, KING));
    southHand.addCard(Card(DIAMONDS, JACK));
    southHand.addCard(Card(SPADES, JACK));
    southHand.addCard(Card(SPADES, FIVE));
    southHand.addCard(Card(DIAMONDS, SIX));
    southHand.addCard(Card(HEARTS, QUEEN));
    southHand.addCard(Card(HEARTS, EIGHT));
    southHand.addCard(Card(CLUBS, SEVEN));
    southHand.addCard(Card(SPADES, FOUR));

    westHand.addCard(Card(SPADES, ACE));
    westHand.addCard(Card(SPADES, TWO));
    westHand.addCard(Card(SPADES, THREE));
    westHand.addCard(Card(CLUBS, EIGHT));
    westHand.addCard(Card(HEARTS, FOUR));
    westHand.addCard(Card(SPADES, QUEEN));
    westHand.addCard(Card(SPADES, SIX));
    westHand.addCard(Card(CLUBS, KING));
    westHand.addCard(Card(HEARTS, TEN));
    westHand.addCard(Card(HEARTS, SIX));
    westHand.addCard(Card(SPADES, EIGHT));
    westHand.addCard(Card(CLUBS, JACK));
    westHand.addCard(Card(SPADES, TEN));

    QMap<PlayerPosition, CardSet> playerHands;
    playerHands.insert(NORTH, northHand);
    playerHands.insert(EAST, eastHand);
    playerHands.insert(SOUTH, southHand);
    playerHands.insert(WEST, westHand);
    serverState.setPlayerHands(playerHands);

    // Test card validation when no cards have been played
    QCOMPARE(serverState.isCardValid(Card(CLUBS, ACE)), false);  // Card not in EAST hand
    QCOMPARE(serverState.isCardValid(Card(DIAMONDS, EIGHT)), true);  // Card in EAST hand

    // Test attributes after playing card
    serverState.updatePlayState(Card(DIAMONDS, EIGHT));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getTricks().value(0).getCard(0) == Card(DIAMONDS, EIGHT), true);
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getPlayerHands().value(EAST).containsCard(Card(DIAMONDS, EIGHT)), false);
    QCOMPARE(spyGameEvent.count(), 1);
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, EIGHT));
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);

    // Test card validation when cards have been played
    QCOMPARE(serverState.isCardValid(Card(HEARTS, THREE)), false);  // Wrong suit, SOUTH has correct suit
    QCOMPARE(serverState.isCardValid(Card(DIAMONDS, TWO)), true);  // Correct suit

    // Test attributes after playing card
    serverState.updatePlayState(Card(DIAMONDS, TWO));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getTricks().value(0).getCard(1), Card(DIAMONDS, TWO));
    QCOMPARE(serverState.getHandToPlay(), WEST);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(serverState.getPlayerHands().value(SOUTH).containsCard(Card(DIAMONDS, TWO)), false);
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, TWO));
    QCOMPARE(spyGameEvent.count(), 1);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);

    // Test card validation when cards have been played
    QCOMPARE(serverState.isCardValid(Card(SPADES, TWO)), true);  // Wrong suit, WEST doesn't have correct suit

    // Test attributes after playing card
    serverState.updatePlayState(Card(SPADES, TWO));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getTricks().value(0).getCard(2), Card(SPADES, TWO));
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getPlayerHands().value(WEST).containsCard(Card(SPADES, TWO)), false);
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, TWO));
    QCOMPARE(spyGameEvent.count(), 1);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);

    // Test attributes after playing 4th card to end trick
    serverState.updatePlayState(Card(DIAMONDS, NINE));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getTricks().value(0).getCard(3), Card(DIAMONDS, NINE));
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getPlayerHands().value(NORTH).containsCard(Card(DIAMONDS, NINE)), false);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 2);
    QCOMPARE(serverState.getTricks().size(), 2);
    QCOMPARE(serverState.getDealer(), EAST);
    QCOMPARE(serverState.getDeclarer(), NORTH);
    QCOMPARE(serverState.getTricksWon(NORTH), 1);
    QCOMPARE(serverState.getTricksWon(EAST), 0);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 0);
    QCOMPARE(serverState.getTricksWon(N_S), 1);
    QCOMPARE(serverState.getTricksWon(E_W), 0);
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, NINE));
    QCOMPARE(spyGameEvent.count(), 3);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 2nd trick where WEST wins with trump card
    serverState.updatePlayState(Card(DIAMONDS, QUEEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, QUEEN));
    serverState.updatePlayState(Card(DIAMONDS, THREE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, THREE));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(DIAMONDS, SIX));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, SIX));
    serverState.updatePlayState(Card(CLUBS, JACK));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, JACK));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getTricks().value(1).getCard(0), Card(DIAMONDS, QUEEN));
    QCOMPARE(serverState.getTricks().value(1).getCard(1), Card(DIAMONDS, THREE));
    QCOMPARE(serverState.getTricks().value(1).getCard(2), Card(DIAMONDS, SIX));
    QCOMPARE(serverState.getTricks().value(1).getCard(3), Card(CLUBS, JACK));
    QCOMPARE(serverState.getHandToPlay(), WEST);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 3);
    QCOMPARE(serverState.getTricks().size(), 3);
    QCOMPARE(serverState.getTricksWon(NORTH), 1);
    QCOMPARE(serverState.getTricksWon(EAST), 0);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 1);
    QCOMPARE(serverState.getTricksWon(E_W), 1);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 3rd trick
    serverState.updatePlayState(Card(SPADES, QUEEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, QUEEN));
    serverState.updatePlayState(Card(SPADES, KING));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, KING));
    serverState.updatePlayState(Card(CLUBS, NINE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, NINE));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(SPADES, FOUR));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, FOUR));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), EAST);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 4);
    QCOMPARE(serverState.getTricksWon(NORTH), 1);
    QCOMPARE(serverState.getTricksWon(EAST), 1);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 1);
    QCOMPARE(serverState.getTricksWon(E_W), 2);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 4th trick
    serverState.updatePlayState(Card(HEARTS, KING));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, KING));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(HEARTS, THREE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, THREE));
    serverState.updatePlayState(Card(HEARTS, FOUR));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, FOUR));
    serverState.updatePlayState(Card(HEARTS, FIVE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, FIVE));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), EAST);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 5);
    QCOMPARE(serverState.getTricksWon(NORTH), 1);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 1);
    QCOMPARE(serverState.getTricksWon(E_W), 3);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 5th trick
    serverState.updatePlayState(Card(CLUBS, QUEEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, QUEEN));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(CLUBS, SEVEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, SEVEN));
    serverState.updatePlayState(Card(CLUBS, EIGHT));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, EIGHT));
    serverState.updatePlayState(Card(CLUBS, ACE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, ACE));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 6);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 2);
    QCOMPARE(serverState.getTricksWon(E_W), 3);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 6th trick
    serverState.updatePlayState(Card(HEARTS, NINE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, NINE));
    serverState.updatePlayState(Card(HEARTS, TWO));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, TWO));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(HEARTS, QUEEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, QUEEN));
    serverState.updatePlayState(Card(HEARTS, SIX));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, SIX));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 7);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 1);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 3);
    QCOMPARE(serverState.getTricksWon(E_W), 3);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 7th trick
    serverState.updatePlayState(Card(HEARTS, ACE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, ACE));
    serverState.updatePlayState(Card(HEARTS, TEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, TEN));
    serverState.updatePlayState(Card(DIAMONDS, FIVE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, FIVE));
    serverState.updatePlayState(Card(HEARTS, SEVEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, SEVEN));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 8);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 1);
    QCOMPARE(serverState.getTricksWon(N_S), 4);
    QCOMPARE(serverState.getTricksWon(E_W), 3);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 8th trick
    serverState.updatePlayState(Card(DIAMONDS, KING));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, KING));
    serverState.updatePlayState(Card(CLUBS, KING));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, KING));
    serverState.updatePlayState(Card(SPADES, SEVEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, SEVEN));
    serverState.updatePlayState(Card(DIAMONDS, SEVEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, SEVEN));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), WEST);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 9);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 2);
    QCOMPARE(serverState.getTricksWon(N_S), 4);
    QCOMPARE(serverState.getTricksWon(E_W), 4);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 9th trick
    serverState.updatePlayState(Card(SPADES, ACE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, ACE));
    serverState.updatePlayState(Card(SPADES, NINE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, NINE));
    serverState.updatePlayState(Card(HEARTS, JACK));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, JACK));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(SPADES, FIVE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, FIVE));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), WEST);
    QCOMPARE(serverState.getPlayerTurn(), WEST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 10);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 2);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 3);
    QCOMPARE(serverState.getTricksWon(N_S), 4);
    QCOMPARE(serverState.getTricksWon(E_W), 5);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 10th trick
    serverState.updatePlayState(Card(SPADES, TEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, TEN));
    serverState.updatePlayState(Card(CLUBS, SIX));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, SIX));
    serverState.updatePlayState(Card(CLUBS, TEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, TEN));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(SPADES, JACK));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, JACK));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), EAST);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 11);
    QCOMPARE(serverState.getTricksWon(NORTH), 2);
    QCOMPARE(serverState.getTricksWon(EAST), 3);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 3);
    QCOMPARE(serverState.getTricksWon(N_S), 4);
    QCOMPARE(serverState.getTricksWon(E_W), 6);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 11th trick
    serverState.updatePlayState(Card(DIAMONDS, ACE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, ACE));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(DIAMONDS, FOUR));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, FOUR));
    serverState.updatePlayState(Card(SPADES, THREE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, THREE));
    serverState.updatePlayState(Card(CLUBS, TWO));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, TWO));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 12);
    QCOMPARE(serverState.getTricksWon(NORTH), 3);
    QCOMPARE(serverState.getTricksWon(EAST), 3);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 3);
    QCOMPARE(serverState.getTricksWon(N_S), 5);
    QCOMPARE(serverState.getTricksWon(E_W), 6);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 12th trick
    serverState.updatePlayState(Card(CLUBS, FIVE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, FIVE));
    serverState.updatePlayState(Card(CLUBS, FOUR));
    QCOMPARE(*serverState.getLastCardPlayed(),Card(CLUBS, FOUR) );
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(HEARTS, EIGHT));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(HEARTS, EIGHT));
    serverState.updatePlayState(Card(SPADES, SIX));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, SIX));
    QCOMPARE(serverState.getPhase(), CARDPLAY);
    QCOMPARE(serverState.getHandToPlay(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getTrickNumber(), 13);
    QCOMPARE(serverState.getTricksWon(NORTH), 4);
    QCOMPARE(serverState.getTricksWon(EAST), 3);
    QCOMPARE(serverState.getTricksWon(SOUTH), 2);
    QCOMPARE(serverState.getTricksWon(WEST), 3);
    QCOMPARE(serverState.getTricksWon(N_S), 6);
    QCOMPARE(serverState.getTricksWon(E_W), 6);
    QCOMPARE(spyGameEvent.count(), 6);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_START);

    // Test attributes after playing 13th trick
    serverState.updatePlayState(Card(CLUBS, THREE));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(CLUBS, THREE));
    serverState.updatePlayState(Card(DIAMONDS, TEN));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, TEN));
    QCOMPARE(serverState.getHandToPlay(), SOUTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);
    serverState.updatePlayState(Card(DIAMONDS, JACK));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(DIAMONDS, JACK));
    serverState.updatePlayState(Card(SPADES, EIGHT));
    QCOMPARE(*serverState.getLastCardPlayed(), Card(SPADES, EIGHT));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getPlayerTurn(), SOUTH);
    QCOMPARE(serverState.getRubberNumber(), 1);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 3);
    QCOMPARE(serverState.getTrickNumber(), 0);
    QCOMPARE(serverState.getDealer(), SOUTH);
    QCOMPARE(serverState.getTricksWon(NORTH), 0);
    QCOMPARE(serverState.getTricksWon(EAST), 0);
    QCOMPARE(serverState.getTricksWon(SOUTH), 0);
    QCOMPARE(serverState.getTricksWon(WEST), 0);
    QCOMPARE(serverState.getTricksWon(N_S), 0);
    QCOMPARE(serverState.getTricksWon(E_W), 0);
    QCOMPARE(spyGameEvent.count(), 7);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAYER_MOVED);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == TRICK_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == PLAY_END);
    arguments = spyGameEvent.takeFirst();
    QVERIFY(arguments.at(0).toInt() == BID_START);

    // Check score after playing 13th trick
    Score score = serverState.getScore();
    QCOMPARE(score.getContractPoints(N_S).size(), 1);
    QCOMPARE(score.getContractPoints(E_W).size(), 1);
    QCOMPARE(score.getContractPoints(N_S).value(0), 0);
    QCOMPARE(score.getContractPoints(E_W).value(0), 0);
    QCOMPARE(score.getGamesWon(N_S), 0);
    QCOMPARE(score.getGamesWon(E_W), 0);
    QCOMPARE(score.getBackScore(N_S), 0);
    QCOMPARE(score.getBackScore(E_W), 0);
    QCOMPARE(score.getOvertricks(N_S), 0);
    QCOMPARE(score.getOvertricks(E_W), 0);
    QCOMPARE(score.getUndertricks(N_S), 0);
    QCOMPARE(score.getUndertricks(E_W), 100);
    QCOMPARE(score.getHonors(N_S), 0);
    QCOMPARE(score.getHonors(E_W), 0);
    QCOMPARE(score.getSlamBonuses(N_S), 0);
    QCOMPARE(score.getSlamBonuses(E_W), 0);
    QCOMPARE(score.getRubberBonuses(N_S), 0);
    QCOMPARE(score.getRubberBonuses(E_W), 0);
    QCOMPARE(score.getTeamVulnerable(N_S), false);
    QCOMPARE(score.getTeamVulnerable(E_W), false);
}
