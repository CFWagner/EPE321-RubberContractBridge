#include "dumbai.h"

DumbAI::DumbAI(QObject *parent) {}

// Indicate to the player it is their turn to bid
void DumbAI::notifyBidTurn()
{
    // Generate random bid
    CardSuit trumpSuit = CardSuit(rand() % 5);
    qint8 tricksAbove = (rand() %  3);
    Bid bid;
    if(tricksAbove == 0){
        bid = Bid(position, PASS);
    }
    else{
        qDebug() << trumpSuit;
        bid = Bid(position, trumpSuit, tricksAbove);
        if(gameState.getCurrentBid() != nullptr && !(bid > *gameState.getCurrentBid()))
            bid = Bid(position, PASS);

    }
    qint64 timeNow = QDateTime::currentMSecsSinceEpoch() + 100; // Add 100ms
    while(timeNow > QDateTime::currentMSecsSinceEpoch()){
         QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    emit bidSelected(bid);
}

// Indicate to the player it is their turn to play a card
void DumbAI::notifyMoveTurn()
{
    // Check if card needs to be played from dummy hand
    CardSet hand;
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        hand = gameState.getDummyHand();
    else
        hand = gameState.getPlayerHand();

    // Check card position is not out of range
    if(playCardPos >= hand.getCardCount())
        playCardPos = 0;
    qint64 timeNow = QDateTime::currentMSecsSinceEpoch() + 100; // Add 100ms
    while(timeNow > QDateTime::currentMSecsSinceEpoch()){
         QCoreApplication::processEvents(QEventLoop::AllEvents);
    }

    emit moveSelected(hand.getCard(playCardPos));
}

// Send the latest available game state tailored to the player
void DumbAI::updateGameState(PlayerGameState gameState)
{
    this->gameState = gameState;
}

// Indicate to the player that the last bid was rejected to the given reason
void DumbAI::notifyBidRejected(QString reason)
{
    emit bidSelected(Bid(position, PASS));
}

// Indicate to the player that the last move was invalid for the given reason
void DumbAI::notifyMoveRejected(QString reason)
{
    // Check if card needs to be played from dummy hand
    CardSet hand;
    if(gameState.getHandToPlay() != gameState.getPlayerTurn() &&
            position == gameState.getDeclarer())
        hand = gameState.getDummyHand();
    else
        hand = gameState.getPlayerHand();

    // Try another card position
    playCardPos++;
    if(playCardPos >= hand.getCardCount())
        playCardPos = 0;
    emit moveSelected(hand.getCard(playCardPos));
}

// Send message to the player where source is the player name
void DumbAI::message(QString source, QString message) {
    QString absorbSource = source;
    QString absorbMessage = message;
}

// Indicate to the player that the game is over
void DumbAI::gameTerminated(QString reason) {
    QString absorbReason = reason;
}
