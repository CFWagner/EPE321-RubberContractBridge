#ifndef TESTSCORE_H
#define TESTSCORE_H

#include <QObject>
#include <QtTest/QtTest>
#include "game-server/score.h"

// Unit test class for Score class
class TestScore : public QObject
{
    Q_OBJECT
public:
    explicit TestScore(QObject *parent = nullptr);
private:
    QMap<PlayerPosition, CardSet> getNSNoTrumpHonorsHand();
    QMap<PlayerPosition, CardSet> getNSClubs4HonorsHand();
    QMap<PlayerPosition, CardSet> getNSClubs5HonorsHand();
private slots:
    void testScore();
};

#endif // TESTSCORE_H
