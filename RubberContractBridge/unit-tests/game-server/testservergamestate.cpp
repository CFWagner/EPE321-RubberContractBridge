#include "testservergamestate.h"
#include "game-server/servergamestate.h"
#include <QSet>

// Default constructor
TestServerGameState::TestServerGameState(QObject *parent) : QObject(parent) {}

// Test for correct construction and operation of ServerGameState class instance
void TestServerGameState::testServerGameState()
{
    // Instantiate ServerGameState
    ServerGameState serverState(NORTH);

    // Verify correct instantiation of attributes
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
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

    // Check that the deck does not contain any duplicate cards
    QVector<Card> deckCardList;
    for(qint8 index = 0; index < serverState.getDeck().getCardCount(); ++ index){
        const Card &card = serverState.getDeck().getCard(index);
        QCOMPARE(deckCardList.contains(card), false);
        deckCardList.append(card);
    }

    // Test deal initiation
    serverState.nextDeal();
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getGameNumber(), 1);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getTrickNumber(), 0);
    QCOMPARE(serverState.getTricks().size(), 0);
    QCOMPARE(serverState.getDealer(), NORTH);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);

    // Test bid validation when no valid bids have been made
    QCOMPARE(serverState.isBidValid(Bid(NORTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DOUBLE)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, REDOUBLE)), false);

    // Make four passes during the bidding phase when no bid has been made and test attributes
    serverState.updateBidState(Bid(NORTH, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);

    serverState.updateBidState(Bid(EAST, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), SOUTH);

    serverState.updateBidState(Bid(SOUTH, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 1);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), WEST);

    serverState.updateBidState(Bid(WEST, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid(), nullptr);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);
    QCOMPARE(serverState.getDealer(), EAST);

    // Test attributes after making a valid bid that isn't a pass
    Bid bid1(EAST, DIAMONDS, 2);
    serverState.updateBidState(bid1);
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder() == bid1.getBidder(), true);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), SOUTH);

    // Test bid validation when one valid bid has been made
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, DOUBLE)), true);
    QCOMPARE(serverState.isBidValid(Bid(SOUTH, REDOUBLE)), false);

    // Test attributes after making a valid double bid
    serverState.updateBidState(Bid(SOUTH, DOUBLE));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid()->getCall(), DOUBLE);
    QCOMPARE(serverState.getCurrentBid()->getTrumpSuit(), DIAMONDS);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), EAST);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), WEST);

    // Test bid validation when one valid double bid has been made
    QCOMPARE(serverState.isBidValid(Bid(WEST, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(WEST, DOUBLE)), false);
    QCOMPARE(serverState.isBidValid(Bid(WEST, REDOUBLE)), true);

    // Test attributes after making a valid redouble bid
    serverState.updateBidState(Bid(WEST, REDOUBLE));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(serverState.getCurrentBid()->getCall(), REDOUBLE);
    QCOMPARE(serverState.getCurrentBid()->getTrumpSuit(), DIAMONDS);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), EAST);
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);

    // Test bid validation when one valid redouble bid has been made
    QCOMPARE(serverState.isBidValid(Bid(NORTH, PASS)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 1)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DIAMONDS, 3)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, CLUBS, 2)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, SPADES, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, NONE, 2)), true);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, DOUBLE)), false);
    QCOMPARE(serverState.isBidValid(Bid(NORTH, REDOUBLE)), false);

    // Test attributes after making a valid bid update
    bid1 = Bid(NORTH, CLUBS, 3);
    serverState.updateBidState(bid1);
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), bid1.getBidder());
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), EAST);

    // Test attributes after 3 passes with a valid current bid
    serverState.updateBidState(Bid(EAST, PASS));
    serverState.updateBidState(Bid(SOUTH, PASS));
    serverState.updateBidState(Bid(WEST, PASS));
    QCOMPARE(serverState.getPhase(), BIDDING);
    QCOMPARE(serverState.getDealNumber(), 2);
    QCOMPARE(*serverState.getCurrentBid() == bid1, true);
    QCOMPARE(serverState.getCurrentBid()->getBidder(), bid1.getBidder());
    QCOMPARE(serverState.getContractBid(), nullptr);
    QCOMPARE(serverState.getPlayerTurn(), NORTH);

    // Teat attributes after 4 passes with a valid current bid
    serverState.updateBidState(Bid(NORTH, PASS));
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
    QCOMPARE(serverState.getHandToPlay(), EAST);
    QCOMPARE(serverState.getPlayerTurn(), EAST);

}
