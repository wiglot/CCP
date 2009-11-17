/*
    CCP - Capacited Clustering Problem.
    Copyright (C) 2009  Wagner Reck (wagner.reck@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "ccpmodel_test.h"
#include <QtTest/QTest>

#include "Instance.h"
#include "Distance.h"
#include "Point.h"

using namespace CCP;


void CCPModel_test::initTestCase()
{
    this->instance = new Instance;
    Point ** points = new Point*[2];
    points[0] = new Point(0.0, 1.0, 1.0);
    points[1] = new Point(1.0, 1.0, 2.0);
    instance->setPoints(points, 2);
    instance->setNumCenters(2);
    instance->setCapacity(6.0);
    Distance * distance = new Distance(instance);
    distance->distance(0,0);
}

void CCPModel_test::init()
{}

void CCPModel_test::cleanup()
{}

void CCPModel_test::cleanupTestCase(){
    delete instance;
}

void CCPModel_test::tight(){
    QCOMPARE(instance->tight(), 0.5); 
}

void CCPModel_test::setPoints(){
    
    
    QCOMPARE(instance->numPoints(), (unsigned short)2);
    QCOMPARE(instance->point(0)->demand(),1.0);
    QCOMPARE(instance->point(1)->demand(),2.0);
    
}
void CCPModel_test::simpleInstance()
{
   
    QCOMPARE(instance->numCenters(), (unsigned short)2);
    QCOMPARE(instance->numPoints(), (unsigned short)2);
    QCOMPARE(instance->distance(0,1), 1.0);
    QCOMPARE(instance->distance(1,1), 0.0);
    QCOMPARE(instance->distance(1,0), 1.0);
    QCOMPARE(instance->capacity(), 6.0);
}


QTEST_MAIN(CCPModel_test)
#include "ccpmodel_test.moc"
