#include "bidcardsselected.h"

BidCardsSelected::BidCardsSelected(CardSuit suit,int bidAmount,QWidget *parent) : QLabel(parent)
{
    this->suit = suit;
    this->bidAmount = bidAmount;
}

CardSuit BidCardsSelected::getSuit()
{
    return suit;
}

int BidCardsSelected::getValue()
{
    return bidAmount;
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
}
