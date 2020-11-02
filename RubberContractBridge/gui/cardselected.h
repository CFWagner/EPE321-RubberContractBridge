#ifndef CARDSELECTED_H
#define CARDSELECTED_H

#include "game-server/bid.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class CardSelected : public QLabel
{
    Q_OBJECT
public:
    explicit CardSelected(QWidget *parent = nullptr);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
    void sendCardPlayed(CardSelected *);

};

#endif // CARDSELECTED_H
