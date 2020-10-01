#include "testcardset.h"

TestCardSet::TestCardSet(QObject *parent) : QObject(parent)
{

}

void TestCardSet::dummy()
{
    QVERIFY(true);
}
