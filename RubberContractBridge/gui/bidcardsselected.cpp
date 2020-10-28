#include "bidcardsselected.h"

BidCardsSelected::BidCardsSelected(BidCall calls,QWidget *parent) : QLabel(parent)
{
    this->calls = calls;
}

BidCardsSelected::BidCardsSelected(CardSuit suit,int bidAmount,QWidget *parent) : QLabel(parent)
{
    this->calls = BID;
    this->suit = suit;
    this->bidAmount = bidAmount;
}

BidCardsSelected::~BidCardsSelected()
{
    delete this;
}

CardSuit BidCardsSelected::getSuit()
{
    return suit;
}

int BidCardsSelected::getValue()
{
    return bidAmount;
}

BidCall BidCardsSelected::getBidCall()
{
    return calls;
}

void BidCardsSelected::enterEvent(QEvent *)
{
    this->move(this->x(),this->y()-10);
}

void BidCardsSelected::leaveEvent(QEvent *)
{
    this->move(this->x(),this->y()+10);
}

void BidCardsSelected::mousePressEvent(QMouseEvent *)
{
    emit sendBidPressed(this);
}
