#include "cardselected.h"

CardSelected::CardSelected(CardSuit suit, CardRank rank,QWidget *parent) : QLabel(parent)
{
    this->suit = suit;
    this->rank = rank;
}

//Move the cards up and down
void CardSelected::enterEvent(QEvent *)
{
    this->move(this->x(),this->y()-10);
}

void CardSelected::leaveEvent(QEvent *)
{
    this->move(this->x(),this->y()+10);
}

void CardSelected::mousePressEvent(QMouseEvent *)
{
    emit sendCardPlayed(this);
}

CardSuit CardSelected::getSuit()
{
    return suit;
}

CardRank CardSelected::getRank()
{
    return rank;
}
