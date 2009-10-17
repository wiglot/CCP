#ifndef CCPTEST_H
#define CCPTEST_H

#include <QtCore/QObject>

class CCPTest : public QObject
{
Q_OBJECT
private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void someTest();
};

#endif // CCPTEST_H
