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
double CCP::Instance::distance (unsigned short p1, unsigned short p2){
    return this->_distance->distance(p1, p2);
}

