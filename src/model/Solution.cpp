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

#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"
#include "Point.h"

using namespace CCP;

/**
 * Constructors/Destructors
 */
Solution::Solution( Instance * instance ) {
    _centers = 0;
    _myInstance = 0;
    _pointsType = 0;
    setInstance( instance );
}

Solution::~Solution() {
    delete [] _centers;
    delete [] _pointsType;
}
/**
 * Methods
 */
void Solution::setPointType( Point* arg1, PointType type ){
  int index = _myInstance->pointIndex(arg1);
  _pointsType[index] = type;
}

void Solution::setInstance( Instance * inst ) {
    //Alloc stuff
    _myInstance = inst;
    if ( _centers != 0 ) {
        delete [] _centers;
    }
    _centers = new Cluster*[inst->numCenters()];
    for (unsigned short count = 0 ; count < inst->numCenters(); ++count){
	_centers[count] = new Cluster(this);
    }
    if ( _pointsType != 0 ) {
        delete [] _pointsType;
    }
    _pointsType = new PointType[inst->numPoints()];

}

void Solution::constructSolution() {
    unsigned short count;
    for ( count = 0; count < _myInstance->numPoints(); ++count ) {
        _pointsType[count] = CCP::Consumer;//Everyone is consumer at begin...
    }

    selectFirstCenters();
    findBasicClusters();
    findBestCenters();

}

void Solution::selectFirstCenters() {
    unsigned short count, center1, center2, numPoints = _myInstance->numPoints();
    short unsigned int nextCenter;
    double distance = 0.0, max = 0.0;
    short unsigned int centerFound;

    for ( count = 0; count < numPoints; ++count ) {
        distance = _myInstance->distance( count, _myInstance->distancesMatrixes()->near( count, numPoints - 1 ) );
        if ( distance > max ) {
            max = distance;
            center1 = count;
            center2 = _myInstance->distancesMatrixes()->near( count, numPoints - 1 );
        }
    }
    _centers[0]->setCenter( _myInstance->point( center1 ) );
//     _pointsType[center1] = CCP::Center;

    _centers[1]->setCenter( _myInstance->point( center2 ) );
//     _pointsType[center2] = CCP::Center;

    int centersInserted = 2;
    while ( _myInstance->numCenters() > centersInserted ) {
        max = 0.0;
        for ( count = 0; count < numPoints; ++count ) {
            if ( _pointsType[count]  == CCP::Consumer ) {
                distance = 1.0;
                for ( int count2 = 0; count2 < centersInserted; ++count2 ) {
                    distance *= _myInstance->distance(
                                    _myInstance->point( count ),
                                    _centers[count2]->getCenter()
                                );
                }
                if ( distance > max ) {
                    max = distance;
                    centerFound = count;
                }
            }
        }
        _centers[centersInserted]->setCenter( _myInstance->point( centerFound ) );
        _pointsType[centerFound] = CCP::Center;
        ++centersInserted;
    }
}

void Solution::findBasicClusters() {
    unsigned short  count, count2;
    Point * selectedPoint;
    unsigned short clusterToAdd;
    double indicator = 0.0;
    
    Cluster * cluster;
    for ( count2 = 0; count2 < _myInstance->numPoints(); ++count2 ) {
        if ( this->_pointsType[count2] == CCP::Consumer ) {
            selectedPoint = _myInstance->point( count2 );
	    indicator = 200000.0;
	    clusterToAdd = _myInstance->numPoints();
            for ( count = 0; count < _myInstance->numCenters(); ++count ) {
                cluster = this->_centers[count];
                if ( cluster->remainCapacity() > selectedPoint->demand() ) {
		    double tmp = _myInstance->distance(selectedPoint, cluster->getCenter(),
							  selectedPoint->demand());
		    if (tmp <= indicator){
			indicator = tmp;
			clusterToAdd = count;
		    }
                }
            }
	    if (clusterToAdd == _myInstance->numPoints()){
	      throw QString ("There is no cluster with capacity to suporte a point");
	    }
	    cluster = this->_centers[clusterToAdd];
	    cluster->addPoint(selectedPoint);
        }
    }
}

void Solution::findBestCenters() {
  Point * newCenter;
  Cluster * cluster;
  unsigned short count, countPoints;
  double value;
  
  for (count = 0; count < _myInstance->numCenters(); ++count){
      cluster = _centers[count];
      value = cluster->totalDistance();
      newCenter = cluster->getCenter();
      for (countPoints = 0; countPoints < cluster->numPoints(); ++countPoints){
	Point * candidacte = cluster->takePoint(0);
	cluster->addPoint(cluster->getCenter());
	cluster->setCenter(candidacte);
	double newValue = cluster->totalDistance();
	if (newValue < value){
	    value = newValue;
	    newCenter = candidacte;
	}
      }
      if (newCenter != cluster->getCenter()){
	  cluster->removePoint(newCenter);
	  cluster->addPoint(cluster->getCenter());
	  cluster->setCenter(newCenter);
      }
  }
}

double Solution::getValue(){
  double acum = 0.0;
  for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
      acum += _centers[i]->totalDistance();
  }
  return acum;
  
}