#include "bidselect.h"

BidSelect::BidSelect(BidCall calls,QWidget *parent) : QLabel(parent)
{
    this->calls = calls;
}

BidSelect::BidSelect(CardSuit suit,int bidAmount,QWidget *parent) : QLabel(parent)
{
    this->calls = BID;
    this->suit = suit;
    this->bidAmount = bidAmount;
}

BidSelect::~BidSelect()
{
    delete this;
}

CardSuit BidSelect::getSuit()
{
    return suit;
}

int BidSelect::getValue()
{
    return bidAmount;
}

BidCall BidSelect::getBidCall()
{
    return calls;
}

//Move the cards up and down
void BidSelect::enterEvent(QEvent *)
{
    this->move(this->x(),this->y()-10);
}

void BidSelect::leaveEvent(QEvent *)
{
    this->move(this->x(),this->y()+10);
}

void BidSelect::mousePressEvent(QMouseEvent *)
{
    emit sendBidPressed(this);
}
