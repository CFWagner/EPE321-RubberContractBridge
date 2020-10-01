#include "testcard.h"
#include<QDebug>

TestCard::TestCard(QObject *parent) : QObject(parent)
{

}

void TestCard::dummy()
{
    QVERIFY(true);
    qDebug("test");
}
