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
#include <densitycluster.h>
#include <QDebug>
#include <QTime>
#include <QMutex>
#include <QProgressDialog>
#include <HMeansCluster.h>
#include <JMeansCluster.h>

using namespace CCP;

/**
 * Constructors/Destructors
 */
Solution::Solution( Instance * instance ) {
    _centers = 0;
    _myInstance = 0;
    setInstance( instance );
    _myIterations = 0;
    _myTime = 0.0;
    _myAlgorithmName = "";
}

Solution::~Solution() {
    if (_centers != 0){
      for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
	  delete _centers[i];
      }
    
      delete [] _centers;
    }
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
    _centers = 0;

}

PointType Solution::pointType (unsigned short index){
  for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
      if (_myInstance->point(index) == _centers[i]->getCenter()){
	  return CCP::Center;
      }
  }
  return CCP::Consumer;
  
}

void Solution::setAlgorithmToUse(HeuristicType type){
    _type = type;
}
void Solution::constructSolution(HeuristicType type) {
    setAlgorithmToUse(type);
    run();
}

void Solution::run() {
//     for ( count = 0; count < _myInstance->numPoints(); ++count ) {
//         _pointsType[count] = CCP::Consumer;//Everyone is consumer at begin...
//     }
    if (!_lock.tryLock()){
        return;
    }
//    QProgressDialog dialog ("Progress of algorithm", "cancel", 0,100);
//
//    dialog.setWindowModality(Qt::WindowModal);
    if (_centers != 0){
	delete [] _centers;
    }
    QTime count;
    count.start();
    switch (_type){
      case Farthest: {
	    FarthestCluster far(_myInstance);
//            connect (&far, SIGNAL(complete(int)), &dialog, SLOT(setValue(int)));
            _centers = far.buildClusters();
            _myAlgorithmName = "Farthest";
            _myIterations = far.iterations();
      }
      break; 
      case Density: {
	    DensityCluster density(_myInstance);
//            connect (&density, SIGNAL(complete(int)), &dialog, SLOT(setValue(int)));
	    _centers = density.buildClusters();	
            _myAlgorithmName = "Density";
            _myIterations = density.iterations();
      }
	break; 
      case HMeans: {
	  HMeansCluster hmean(_myInstance);
//          connect (&hmean, SIGNAL(complete(int)), &dialog, SLOT(setValue(int)));
	  _centers = hmean.buildClusters();
          _myAlgorithmName = "HMeans";
          _myIterations = hmean.iterations();
      }break;
      case JMeans: {
              JMeansCluster jmean(_myInstance);
//              connect (&jmean, SIGNAL(complete(int)), &dialog, SLOT(setValue(int)));
              _centers = jmean.buildClusters();
              _myAlgorithmName = "JMeans";
              _myIterations = jmean.iterations();
      }break;
    }

    _myTime = count.elapsed()/1000.0;
//    dialog.setValue(100);
    _lock.unlock();
   
    emit finished();
}

Point * Solution::centerOfCluster(unsigned short index){
      return this->cluster(index)->getCenter();
}

double Solution::getValue(){
  double acum = 0.0;
  for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
      acum += _centers[i]->totalDistance();
  }
  return acum;
}

const bool Solution::isValid(){

    if (_centers == 0){
        return false;
    }

  int numPoints = instance()->numPoints();
  int numCenters = instance()->numCenters();
  QScopedArrayPointer<bool> visited (new bool[numPoints]);
  
  bool notFailed = true;
  unsigned short i, j;
  for (i =0; i < numPoints; ++i){
      visited[i] = false;
  }
  for (i = 0; i < numCenters; ++i){
      Cluster * clusterTMP = cluster(i);
      if (visited[clusterTMP->getCenter()->index()]){
	  qDebug () << QString("Point %1 (as Center of cluster %2) is inserted twice (at least)")
                                      .arg(clusterTMP->getCenter()->index())
				      .arg(i);
	  notFailed = false;
      }
      visited[clusterTMP->getCenter()->index()] = true;

      for (j = 0; j < clusterTMP->numPoints(); ++j){
          Point* point = clusterTMP->getPoint(j);
          if (visited[point->index()]){
	      qDebug () << QString("Point %1 (as point of cluster %2) is inserted twice (at least)")
                                      .arg(point->index())
				      .arg(i);
		notFailed = false;
	  }

          visited[point->index()] = true;
      }
      if (clusterTMP->remainCapacity() < 0.0){
            qDebug() << QString("Over demand on cluster %1").arg(i);
            notFailed = false;
      }
  }

  for (i =0; i < numPoints; ++i){
      if (visited[i] == false){
	qDebug() << QString ("Point %1 was not visited.").arg(i);
	notFailed = false;
      }
  }
  
  return notFailed;
}
