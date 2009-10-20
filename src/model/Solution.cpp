#include "Solution.h"
#include "Instance.h"

using namespace CCP;

/**
 * Constructors/Destructors
 */
/**
 * Methods
 */

void Solution::setInstance (Instance * inst){
  //Alloc stuff
  _myInstance = inst;
}

void Solution::constructSolution(){
  unsigned short count;
  for (count = 0; count < _myInstance->numPoints(); ++count)
    _pointsType[count] = CCP::Consumer;//Everyone is consumer at begin...
  
  selectFirstCenters();
  
  findBasicClusters();
  
  findBestCenters();
    
}

void Solution::selectFirstCenters(){
  unsigned short count, center1, center2, numPoints = _myInstance->numPoints();
  short unsigned int nextCenter;
  double distance = 0.0, max = 0.0;
  
  for (count = 0; count < numPoints; ++count){
    distance = _myInstance->distance(count, _myInstance->distancesMatrixes()->near(count,numPoints-1));
    if (distance > max){
	max = distance;
	center1 = count;
	center2 = _myInstance->distancesMatrixes()->near(count,numPoints-1);
    }
  }
  _centersIndex[0] = center1;
  _pointsType[center1] = CCP::Center;
  
  _centersIndex[1] = center2;
  _pointsType[center2] = CCP::Center;
  
  int centersInserted = 2;
  while (_myInstance->numCenters() > centersInserted){
    max = 0.0;
    for (count = 0; count < numPoints; ++count){
      if (_pointsType[count]  == CCP::Consumer){
	distance = 1.0;
	  for (int count2 = 0; count2 < centersInserted; ++count2){
	    distance *= _myInstance->distance(count, _centersIndex[count2]);
	  }
	  if (distance > max){
	      max = distance;
	      _centersIndex[centersInserted] = count;
	  }
      }
    }
    
    _pointsType[_centersIndex[centersInserted]] = CCP::Center;
    ++centersInserted;
  }
}

void Solution::findBasicClusters(){


}

void Solution::findBestCenters(){
  
}