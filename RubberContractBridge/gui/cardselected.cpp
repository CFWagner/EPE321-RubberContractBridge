#include "cardselected.h"

CardSelected::CardSelected(QWidget *parent) : QLabel(parent)
{
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
