#include "playcardselected.h"

PlayCardSelected::PlayCardSelected(QWidget *parent) : QLabel(parent)
{

}

void PlayCardSelected::enterEvent(QEvent *)
{
    this->move(this->x(),this->y()-40);
}

void PlayCardSelected::leaveEvent(QEvent *)
{
    this->move(this->x(),this->y()+40);
}

void PlayCardSelected::mousePressEvent(QMouseEvent *)
{
    emit sendCardPlayed(this);
}
