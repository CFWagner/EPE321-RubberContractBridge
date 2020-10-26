#ifndef TESTPLAYERGAMESTATE_H
#define TESTPLAYERGAMESTATE_H

#include <QObject>
#include <QTest>

// Unit test class for PlayerGameState class
class TestPlayerGameState : public QObject
{
    Q_OBJECT
public:
    explicit TestPlayerGameState(QObject *parent = nullptr);

private slots:
    void testPlayerGameState();
};

#endif // TESTPLAYERGAMESTATE_H
