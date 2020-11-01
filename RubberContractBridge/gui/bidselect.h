#ifndef BIDSELECT_H
#define BIDSELECT_H

#include "game-server/bid.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class BidSelect : public QLabel
{
    Q_OBJECT
public:
    explicit BidSelect(BidCall calls,QWidget *parent = nullptr);
    explicit BidSelect(CardSuit suit,int bidAmount, QWidget *parent = nullptr);
    ~BidSelect();
    CardSuit getSuit();
    int getValue();
    BidCall getBidCall();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void sendBidPressed(BidSelect *);
private:

    CardSuit suit;
    int bidAmount;
    QWidget *parent;
    BidCall calls = BID;
};

#endif // BIDCARDSSELECTED_H
