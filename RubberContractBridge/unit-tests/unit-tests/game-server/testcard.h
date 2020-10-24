#ifndef TESTCARD_H
#define TESTCARD_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "game-server/card.h"

// Unit test class for Card class
class TestCard : public QObject
{
    Q_OBJECT
public:
    explicit TestCard(QObject *parent = nullptr);

private slots:
    void testCard();
};

#endif // TESTCARD_H
