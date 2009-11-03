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

#include "CCPRead.h"
#include "Instance.h"
#include "readccp.h"
#include <QTest>

using namespace CCP;

void CCPRead::initTestCase(){
  
}

void CCPRead::init(){
  
}
void CCPRead::cleanup(){
  
}
void CCPRead::cleanupTestCase(){
  
}

void CCPRead::simpleTXT(){
    Instance * inst = readCCP::readSimpleTXT("instance1.txt");
    QVERIFY(inst != (Instance*) 0);
    QCOMPARE(inst->name(), QString("instance 1")); 
    QCOMPARE(inst->capacity(), 5.0);
    QCOMPARE(inst->numCenters(), (unsigned short)3);
    QCOMPARE(inst->numPoints(), (unsigned short) 6);
}

QTEST_MAIN(CCPRead)
#include "CCPRead.moc"