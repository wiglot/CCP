#include "CCPTest.h"
#include <QtTest/QTest>

void CCPTest::initTestCase()
{}

void CCPTest::init()
{}

void CCPTest::cleanup()
{}

void CCPTest::cleanupTestCase()
{}

void CCPTest::someTest()
{
    QCOMPARE(1,2);
}


QTEST_MAIN(CCPTest)
#include "CCPTest.moc"
