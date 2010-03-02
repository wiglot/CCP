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
    void hillClimb1();
};

#endif // CCPSOLUTIONIMPROVEMENT_TEST_H
