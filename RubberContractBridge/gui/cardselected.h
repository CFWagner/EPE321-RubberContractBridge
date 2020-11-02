#ifndef CARDSELECTED_H
#define CARDSELECTED_H

#include "game-server/bid.h"
#include "enumerations/CardRank.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class CardSelected : public QLabel
{
    Q_OBJECT
public:
    explicit CardSelected(CardSuit suit,CardRank rank, QWidget *parent = nullptr);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    CardSuit getSuit();
    CardRank getRank();
signals:
    void sendCardPlayed(CardSelected *);
private:
    CardSuit suit;
    CardRank rank;
};

#endif // CARDSELECTED_H
