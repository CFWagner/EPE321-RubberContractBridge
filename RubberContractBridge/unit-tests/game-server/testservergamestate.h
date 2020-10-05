#ifndef TESTSERVERGAMESTATE_H
#define TESTSERVERGAMESTATE_H

#include <QObject>
#include <QtTest/QtTest>

class TestServerGameState : public QObject
{
    Q_OBJECT
public:
    explicit TestServerGameState(QObject *parent = nullptr);
    void testServerGameState();
};

#endif // TESTSERVERGAMESTATE_H
