#ifndef TESTAI_H
#define TESTAI_H
#include "ai/ai.h"
#include <QtTest>
class testai : public QObject
{
    Q_OBJECT
public:
    explicit testai(QObject *parent = nullptr);

private slots:
    void testHandGenerate();

};

#endif // TESTAI_H
