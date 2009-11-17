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

/**ToDo
      Density by points
      penalty(regret) by points
*/
#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"
#include "Point.h"
#include "farthestcluster.h"

using namespace CCP;

/**
 * Constructors/Destructors
 */
Solution::Solution( Instance * instance ) {
    _centers = 0;
    _myInstance = 0;
    setInstance( instance );
}

Solution::~Solution() {
    delete [] _centers;
//     delete [] _pointsType;
}
/**
 * Methods
 */
// void Solution::setPointType( Point* arg1, PointType type ){
//   int index = _myInstance->pointIndex(arg1);
//   _pointsType[index] = type;
// }

void Solution::setInstance( Instance * inst ) {
    //Alloc stuff
    _myInstance = inst;
    if ( _centers != 0 ) {
        delete [] _centers;
    }
    _centers = 0;/*new Cluster*[inst->numCenters()];
    for (unsigned short count = 0 ; count < inst->numCenters(); ++count){
	_centers[count] = new Cluster(this);
    }
    if ( _pointsType != 0 ) {
        delete [] _pointsType;
    }
    _pointsType = new PointType[inst->numPoints()];
    */

}

PointType Solution::pointType (unsigned short index){
  for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
      if (_myInstance->point(index) == _centers[i]->getCenter()){
	  return CCP::Center;
      }
  }
  return CCP::Consumer;
  
}

void Solution::constructSolution(HeuristicType type) {
//     for ( count = 0; count < _myInstance->numPoints(); ++count ) {
//         _pointsType[count] = CCP::Consumer;//Everyone is consumer at begin...
//     }
    switch(type){
      
      case CCP::Density:

	break;
	
      case CCP::Farthest :
	FarthestCluster far(_myInstance);
	_centers = far.buildClusters();
// 	selectFirstCenters();
// 	findBasicClusters();	
// 	findBestCenters();
	break;
    }

}



double Solution::getValue(){
  double acum = 0.0;
  for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
      acum += _centers[i]->totalDistance();
  }
  return acum;
  
}