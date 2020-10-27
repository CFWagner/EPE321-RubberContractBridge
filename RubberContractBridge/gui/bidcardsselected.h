#ifndef BIDCARDSSELECTED_H
#define BIDCARDSSELECTED_H

#include "game-server/bid.h"


#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class BidCardsSelected : public QLabel
{
    Q_OBJECT
public:
    explicit BidCardsSelected(CardSuit suit,int bidAmount, QWidget *parent = nullptr);
    CardSuit getSuit();
    int getValue();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
private:
    CardSuit suit;
    int bidAmount;
};

#endif // BIDCARDSSELECTED_H
