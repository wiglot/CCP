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

#include "History.h"
#include "Point.h"

using namespace CCP;


HistoryStep::HistoryStep() {

}

void HistoryStep::AssignCluster ( Cluster* cluster ) {
    if (cluster->getCenter() == 0){ //All points are considered not inserted in cluster
        return;
    }
    for(int i = 0; i < cluster->numPoints(); ++i){
        Point * p = cluster->getPoint(i);
        while (p->index() >= assign.size()){
            assign.append(-1);
        }
        assign[p->index()] = cluster->getCenter()->index();
    }

    Point * p = cluster->getCenter();
    while (p->index() >= assign.size()){
        assign.append(-1);
    }
    assign[p->index()] = cluster->getCenter()->index();
}

int HistoryStep::assignedTo ( int index ) {
    if (index < assign.size()){
        return assign.at(index);
    }
    return -1;
}


int HistoryStep::assignedTo ( Point* p ) {
    return assignedTo(p->index());
}



History::History() {
    _actualIteration = 0;
    _actualStep = 0;
    HistoryStep step;
    appendStep(step);
    finishIteration();
}

History::~History() {

}



void History::begin() {
    _actualIteration = 0;
    _actualStep = 0;
}


bool History::hasNextIteration() {

    return (_actualIteration < (iterations.size()-1));
}


void History::nextIteration() {
    if (hasNextIteration()){
        _actualIteration+= 1;
        _actualStep = iterations.at(_actualIteration);
    }
}


void History::end() {
    if (iterations.size() > 0){
        _actualIteration = iterations.count()-1;
        _actualStep = steps.count()-1;
    }
}


bool History::goToIteration ( int iter ) {
    if (iter < iterations.size() && iter > 0){
        _actualIteration = iter;
        _actualStep = iterations.at(_actualIteration);
        return true;
    }
    return false;
}


HistoryStep History::moveSteps ( int stp ) {
    if (stp > 0){
        if ((stp + _actualStep) >= stepsCount()){
            _actualStep = stepsCount()-1;
        }else{
            _actualStep += stp;
        }
    }else {
        if (( _actualStep - stp) < 0){
            _actualStep = 0;
        }else{
            _actualStep -= stp;
        }
    }

    return steps.at(actualStep());
}


int History::stepsCount() {
    return steps.count();
}


void History::appendStep ( const CCP::HistoryStep step ) {
    steps.append(step);
}


void History::finishIteration() {
    iterations.append(_actualStep);
//     _actualIteration++;
}




