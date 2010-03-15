#ifndef CCPSOLUTIONIMPROVEMENT_TEST_H
#define CCPSOLUTIONIMPROVEMENT_TEST_H

#include <QObject>
namespace CCP{
    class Instance;
}
class CCPSolutionImprovement_Test : public QObject
{
Q_OBJECT
    CCP::Instance* _instance;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void cleanup();
    void hillClimbShift1();
    void hillClimbInterchange1();

    void SAShift1();

    void SAInterchange1();


};

#endif // CCPSOLUTIONIMPROVEMENT_TEST_H
