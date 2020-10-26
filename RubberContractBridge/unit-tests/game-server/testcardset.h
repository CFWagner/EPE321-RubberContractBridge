#ifndef TESTCARDSET_H
#define TESTCARDSET_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "game-server/cardset.h"

// Unit test class for CardSet class
class TestCardSet : public QObject
{
    Q_OBJECT
public:
    explicit TestCardSet(QObject *parent = nullptr);

private slots:
    void testCardSet();

};

#endif // TESTCARDSET_H
