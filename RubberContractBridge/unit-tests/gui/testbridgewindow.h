#ifndef TESTBRIDGEWINDOW_H
#define TESTBRIDGEWINDOW_H

#include "gui/bridgewindow.h"
#include <QtTest/QtTest>
#include <QObject>

class testBridgeWindow : public QObject
{
    Q_OBJECT
public:
    explicit testBridgeWindow(QObject *parent = nullptr);
    ~testBridgeWindow();
private slots:
    void testBridge();
signals:
    void updateGameState(PlayerGameState);
private:
    bridgeWindow *testPlayN;
    bridgeWindow *testPlayE;
    bridgeWindow *testPlayS;
    bridgeWindow *testPlayW;
    QSignalSpy *sendGS;
};

#endif // TESTBRIDGEWINDOW_H
