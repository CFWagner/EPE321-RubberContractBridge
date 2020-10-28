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
    explicit BidCardsSelected(BidCall calls,QWidget *parent = nullptr);
    explicit BidCardsSelected(CardSuit suit,int bidAmount, QWidget *parent = nullptr);
    ~BidCardsSelected();
    CardSuit getSuit();
    int getValue();
    BidCall getBidCall();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
    void sendBidPressed(BidCardsSelected *);
private:
    CardSuit suit;
    int bidAmount;
    QWidget *parent;
    BidCall calls = BID;
};

#endif // BIDCARDSSELECTED_H
