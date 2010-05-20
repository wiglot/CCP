/*
Wagner de Melo Reck (wagner.reck@gmail.com)

CCP

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

#include "CCPHistory.h"
#include "../src/model/History.h"
#include <QtTest>
#include <Solution.h>

using namespace CCP;

void CCPHistory::initTestCase()
{
    this->instance = new Instance;
    Point ** points = new Point*[6];
    points[0] = new Point(instance,0.0, 2.0, 1.0);
    points[1] = new Point(instance,0.0, 0.0, 1.0);
    points[2] = new Point(instance,1.0, 1.0, 1.0);
    points[3] = new Point(instance,2.0, 1.0, 1.0);
    points[4] = new Point(instance,3.0, 0.0, 1.0);
    points[5] = new Point(instance,3.0, 2.0, 1.0);
    instance->setPoints(points, 6);
    instance->setNumCenters(2);
    instance->setCapacity(3.5);
    new Distance(instance);
}

void CCPHistory::checkHistory(){
    Solution * sol = new Solution(instance);
    sol->constructSolution(CCP::Density);
    QVERIFY(0 != sol->history());
//     QCOMPARE (0, sol->history()->stepsCount());

    QVERIFY( sol->history()->stepsCount() != 0 );
}

void CCPHistory::changeIteraction() {
    Solution * sol = new Solution(instance);
    sol->constructSolution(CCP::HMeans);
    History * h = sol->history();
    h->begin();
    if (h->hasNextIteration()){
        h->nextIteration();
    }else{
        qDebug() << sol->iterations();
        QWARN("No next iteration!");
    }
}


void CCPHistory::firstStep() {
    Solution * sol = new Solution(instance);
    sol->constructSolution(CCP::HMeans);
    History * h = sol->history();
    h->begin();
    HistoryStep step = h->moveSteps(0);
    for (int i = 0; i < instance->numPoints(); ++i){
        QCOMPARE (-1, step.assignedTo(i));
    }
}

void CCPHistory::lastStep() {
    Solution * sol = new Solution(instance);
    sol->constructSolution(CCP::HMeans);
    History * h = sol->history();
    if (sol->isValid()){
        h->end();
        HistoryStep step = h->moveSteps(0);
        for (int i = 0; i < instance->numPoints(); ++i){
            QVERIFY (-1 != step.assignedTo(i));
        }
    }else{
        QWARN("Invalid Solution! Test skipped!");
    }
}



void CCPHistory::changeSteps() {
    Solution * sol = new Solution(instance);
    sol->constructSolution(CCP::HMeans);
    History * h = sol->history();


    h->end();
    int step = h->actualStep();
    QCOMPARE(step, h->actualStep());
    h->begin();
    QVERIFY(step != h->actualStep());

}


QTEST_MAIN(CCPHistory)
#include "CCPHistory.moc"
