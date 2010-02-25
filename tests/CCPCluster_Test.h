#ifndef CCPCLUSTER_TEST_H
#define CCPCLUSTER_TEST_H


#include <QObject>
#include <Instance.h>
class CCPCluster_Test : public QObject
{
Q_OBJECT
    CCP::Instance * _instance;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void cleanup();
    void interchangeSimple();
    void invalidInterchangeSimple();
    void interchangeSimpleUndo();
    void invalidInterchangeSimpleUndo();
    void interchangeDouble();
    void invalidInterchangeDouble();
    void interchangeDoubleUndo();
    void invalidInterchangeDoubleUndo();
};

#endif // CCPCLUSTER_TEST_H
