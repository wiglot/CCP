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

#ifndef HISTORY_H
#define HISTORY_H
// #include "model_global.h"
#include <QList>
#include "Cluster.h"

namespace CCP{

class HistoryStep{
    QList <int> assign;
    public:
        HistoryStep();
        void AssignCluster(Cluster* cluster);
        int assignedTo(int index);
        int assignedTo(Point* p);

};

class History {
    private:
        QList<HistoryStep> steps;
        QList<int> iterations;
        int _actualStep;
        int _actualIteration;

    public:
        History();
        ~History();
//         int size();

            void finishIteration();
            void appendStep(const CCP::HistoryStep step);


            /** isn't last iteration? */
            bool hasNextIteration();
            /**Walk one iteration forward*/
            void nextIteration();

            bool goToIteration(int iter);
            /** Go to fisrt step of first iteration */
            void begin();
            /** Go to last step of last iteration */
            void end();

            /**Return the steps in current iteration */
            int stepsCount();

            int actualStep(){return _actualStep;};
            /** chango \stp in current iteration. return true if was possible change at least one step.
            Negative values walk backwards. In case of number of steps be bigger than avaliable in the direction,
            History will walk the avaliable steps.*/
            HistoryStep moveSteps(int stp);
            inline HistoryStep stepFoward( ) { return moveSteps(1); }
            inline HistoryStep stepBackward() { return moveSteps(-1); };

};
}

#endif // HISTORY_H
