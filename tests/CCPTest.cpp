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

#include "CCPTest.h"
#include <QtTest/QTest>
#include "Instance.h"
#include "readccp.h"

using namespace CCP;

void CCPTest::initTestCase()
{
_instance = new Instance();
    Point ** points = new Point*[6];
    points[0] = new Point(_instance, 0.0, 2.0, 1.0);
    points[1] = new Point(_instance,0.0, 0.0, 1.0);
    points[2] = new Point(_instance,1.0, 1.0, 1.0);
    points[3] = new Point(_instance,2.0, 1.0, 1.0);
    points[4] = new Point(_instance,3.0, 0.0, 1.0);
    points[5] = new Point(_instance,3.0, 2.0, 1.0);
    _instance->setPoints(points, 6);
    _instance->setNumCenters(2);
    _instance->setCapacity(4.0);
    new Distance(_instance);
}

void CCPTest::init()
{}

void CCPTest::cleanup()
{}

void CCPTest::cleanupTestCase()
{}

void CCPTest::someTest()
{
  QWARN(QString::number(_instance->tight()).toAscii());
      _instance->setTight(1.5);
    QCOMPARE(1.5,_instance->tight());
}


QTEST_MAIN(CCPTest)
#include "CCPTest.moc"
