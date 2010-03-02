#include "CCPSolutionImprovement_Test.h"
#include <QTest>
#include <Instance.h>
#include <Solution.h>
#include <SolutionImprovement.h>
#include <Distance.h>

using namespace CCP;

void CCPSolutionImprovement_Test::initTestCase(){
    this->_instance = new Instance;
     Point ** points = new Point*[6];
     points[0] = new Point(0.0, 2.0, 1.0);
     points[1] = new Point(0.0, 0.0, 1.0);
     points[2] = new Point(1.0, 1.0, 1.0);
     points[3] = new Point(2.0, 1.0, 1.0);
     points[4] = new Point(3.0, 0.0, 1.0);
     points[5] = new Point(3.0, 2.0, 1.0);
     _instance->setPoints(points, 6);
     _instance->setNumCenters(2);
     _instance->setCapacity(4.0);
     new Distance(_instance);
}

void CCPSolutionImprovement_Test::cleanupTestCase(){
    QFAIL("Not implemented yet");
}

void CCPSolutionImprovement_Test::cleanup(){
    QFAIL("Not implemented yet");
}

void CCPSolutionImprovement_Test::hillClimb1(){
    QFAIL("Not implemented yet");
//    Solution * orig = new Solution(_instance);
//    orig->constructSolution(Farthest);
//
//    SolutionImprovement improve(*orig);
//    Solution * improved = improve.hillClimb();
//
//    delete orig;
//    delete improved;

}

QTEST_MAIN(CCPSolutionImprovement_Test)
#include "CCPSolutionImprovement_Test.moc"
