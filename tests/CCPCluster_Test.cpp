#include "CCPCluster_Test.h"
#include <QTest>
#include <Instance.h>
#include <Solution.h>
#include <Cluster.h>

using namespace CCP;

void CCPCluster_Test::initTestCase(){
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
     new Distance(_instance);
}

void CCPCluster_Test::cleanupTestCase(){
    delete _instance;
}

void CCPCluster_Test::cleanup(){
    for (int i = 0; i < _instance->numPoints(); ++i){
        _instance->point(i)->setDemand(1.0);
    }
}

void CCPCluster_Test::interchangeSimple(){
    _instance->setCapacity(4.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QVERIFY(sol.isValid());

    Point * p = _instance->point(0);

    InterchangeResult result = sol.cluster(0)->shift(p, sol.cluster(1));
    QVERIFY(result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 1);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 1);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 3);
    QCOMPARE(int(sol.cluster(1)->getPoint(2)->index()), 0);
}
void CCPCluster_Test::invalidInterchangeSimple(){
    _instance->setCapacity(3.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);


    QVERIFY(sol.isValid());

    Point * p = _instance->point(0);

    InterchangeResult result = sol.cluster(0)->shift(p, sol.cluster(1));
    QVERIFY(!result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
}

void CCPCluster_Test::interchangeSimpleUndo(){
    _instance->setCapacity(4.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QVERIFY(sol.isValid());

    Point * p = _instance->point(0);

    InterchangeResult result = sol.cluster(0)->shift(p, sol.cluster(1));
    QVERIFY(result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 1);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 1);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 3);
    QCOMPARE(int(sol.cluster(1)->getPoint(2)->index()), 0);

    result.undo();

    QVERIFY( ! result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
}

void CCPCluster_Test::invalidInterchangeSimpleUndo(){
    _instance->setCapacity(4.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QVERIFY(sol.isValid());

    Point * p = _instance->point(0);

    InterchangeResult result = sol.cluster(0)->shift(p, sol.cluster(1));
    QVERIFY(result.isValid());

    _instance->point(1)->setDemand(3.0);
    QVERIFY( !result.undo());

    QVERIFY( ! result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 1);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 1);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 3);
    QCOMPARE(int(sol.cluster(1)->getPoint(2)->index()), 0);

}

void CCPCluster_Test::interchangeDouble(){
    _instance->setCapacity(3.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(0)->index()), 4);
    QVERIFY(sol.isValid());


    Point * p1 = _instance->point(0);
    Point * p2 = _instance->point(4);

    InterchangeResult result = sol.cluster(0)->interchange(p1,p2, sol.cluster(1));
    QVERIFY(result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 4);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(1)->index()), 0);

}

void CCPCluster_Test::invalidInterchangeDouble(){
    _instance->setCapacity(3.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(0)->index()), 4);
    QVERIFY(sol.isValid());

    _instance->point(2)->setDemand(0.5);
    Point * p1 = _instance->point(0);
    p1->setDemand(1.5);

    Point * p2 = _instance->point(4);

    InterchangeResult result = sol.cluster(0)->interchange(p1,p2, sol.cluster(1));
    QVERIFY( ! result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(0)->index()), 4);
}

void CCPCluster_Test::interchangeDoubleUndo(){
    _instance->setCapacity(3.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);

    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(0)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(0)->index()), 4);
    QVERIFY(sol.isValid());


    Point * p1 = _instance->point(0);
    Point * p2 = _instance->point(4);

    InterchangeResult result = sol.cluster(0)->interchange(p1,p2, sol.cluster(1));
    QVERIFY(result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 4);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(1)->index()), 0);

    result.undo();

    QVERIFY( ! result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 0);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);


}

void CCPCluster_Test::invalidInterchangeDoubleUndo(){
    _instance->setCapacity(3.0);
    Solution sol(_instance);
    sol.constructSolution(CCP::Farthest);
    QVERIFY(sol.isValid());


    Point * p1 = _instance->point(0);
    Point * p2 = _instance->point(4);

    InterchangeResult result = sol.cluster(0)->interchange(p1,p2, sol.cluster(1));
    QVERIFY(result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 4);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(1)->index()), 0);

    _instance->point(1)->setDemand(0.5);
    p2->setDemand(1.5);

    QVERIFY( ! result.undo());

    QVERIFY( ! result.isValid());
    QVERIFY(sol.isValid());
    QCOMPARE(int(sol.cluster(0)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(0)->getPoint(1)->index()), 4);
    QCOMPARE(int(sol.cluster(1)->numPoints()), 2);
    QCOMPARE(int(sol.cluster(1)->getPoint(1)->index()), 0);
}

QTEST_MAIN(CCPCluster_Test)
#include "CCPCluster_Test.moc"
