#include "Instance.h"
#include "Distance.h"


/**
 * Constructors/Destructors
 */
CCP::Instance::~Instance(){
    unsigned short count;
//     for (count = 0; count < this->_numPoints; ++count)
//       delete _points;
    delete [] _points;
    delete _distance;
}
/**
 * Methods
 */
double CCP::Instance::distance (short unsigned int p1, short unsigned int p2, double factor){
    return this->_distance->distance(p1, p2) * factor;
}

double CCP::Instance::distance (Point * p1, Point * p2, double factor){
  unsigned short count, point1 = 0, point2 = 0;
    for (count = 0; count < _numPoints; ++count){
      if (_points[count] == p1){
	  point1 = count;
	  if (point2 != 0){
	    break;
	  }
      }
      if (_points[count] == p2){
	  point1 = count;
	  if (point1 != 0){
	    break;
	  }
      }
    }
    return this->distance(point1, point2, factor);
}


double CCP::Instance::tight(){
  double acum = 0.0;
   for (int i = 0; i < this->_numPoints; ++i){
      acum += _points[i]->demand();
   }
   return acum/this->capacity();
}