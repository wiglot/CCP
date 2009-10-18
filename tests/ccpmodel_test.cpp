/*
    CCP (Capacited Clusterin Problem)
    Copyright (C) 2009  Wagner Reck

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

void CCPModel_test::initTestCase()
{}

void CCPModel_test::init()
{}

void CCPModel_test::cleanup()
{}

void CCPModel_test::cleanupTestCase()
{}

void CCPModel_test::simpleInstance()
{
  //dumb test
    QCOMPARE(1,2);
}


QTEST_MAIN(CCPModel_test)
#include "ccpmodel_test.moc"
