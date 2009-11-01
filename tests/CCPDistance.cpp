/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "CCPDistance.h"
#include "Point.h"
#include "Distance.h"
#include "Instance.h"

#include <QTest>

using namespace CCP;

void CCPDistance::distance(){
    Instance * instance = new Instance;
    Point ** points = new Point*[2];
    points[0] = new Point(0.0, 1.0, 1.0);
    points[1] = new Point(1.0, 1.0, 2.0);
    instance->setPoints(points, 2);
    Distance * distance = new Distance(instance);
    instance->setDistances(distance);
    QCOMPARE(distance->distance(0,1), 1.0);
    QCOMPARE(distance->distance(0,0), 0.0);
    QCOMPARE(distance->distance(1,0), 1.0);
}

void CCPDistance::distance2Points(){

    Point ** points = new Point*[2];
    points[0] = new Point(0.0, 1.0, 1.0);
    points[1] = new Point(1.0, 1.0, 2.0);

    QCOMPARE(points[0]->position().distance(points[1]->position()), 1.0);

}

void CCPDistance::near(){
    Instance * instance = new Instance;
    Point ** points = new Point*[4];
    points[0] = new Point(0.0, 0.0, 1.0);
    points[1] = new Point(0.0, 1.0, 2.0);
    points[2] = new Point(0.0, 2.0, 3.0);
    points[3] = new Point(0.0, 3.0, 4.0);
    instance->setPoints(points, 4);
    Distance * distance = new Distance(instance);
    instance->setDistances(distance);
    QCOMPARE(distance->near(0,0), (unsigned short)0);
    QCOMPARE(distance->near(0,1), (unsigned short)1);
    QCOMPARE(distance->near(0,2), (unsigned short)2);
    QCOMPARE(distance->near(0,3), (unsigned short)3);
}

QTEST_MAIN(CCPDistance)
#include "CCPDistance.moc"
