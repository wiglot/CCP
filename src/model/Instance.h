#ifndef INSTANCE_H
#define INSTANCE_H
#include <string>
#include "Distance.h"
#include "Point.h"

namespace CCP {

class Solution;
/**
 * Class Instance
 */
class Instance {
    /**
     * Public stuff
     */
public:
    /**
     * Empty Constructor
     */
    Instance ( ) { }
    /** Basic Destructor
    */
    ~Instance( );
    /**
     * Accessor Methods
     */
    /**
     *
     */
    unsigned short numCenters ( ) {
        return _numCenters;
    }
    /**
     *
     */
    void setNumCenters (unsigned short value ) {
        _numCenters = value;
    }
    
    unsigned short numPoints(){ return _numPoints;   }
    /**
     *
     */
    Point * point (unsigned short index ) {
      if (index < _numPoints){
        return _points[index];
      } else {
	return 0;
      }
    }
    /**
     *
     */
    void setPoints (Point ** value, unsigned short numPoints) {
        _points = value;
	this->_numPoints = numPoints;
    }
    /**
    * Overloaded function, same that instance::distancesMatrixes()->distance(p1, p2)
    */
    double distance (unsigned short p1, unsigned short p2, double factor = 1);
    
    
    double distance (Point * p1, Point * p2, double factor = 1);
    /**
     *
     */
    CCP::Distance * distancesMatrixes ( ) {
        return _distance;
    }
    /**
     *
     */
    void setDistances (CCP::Distance * value ) {
        _distance = value;
    }
    /**
     *
     */
    Solution * solutions ( unsigned short index) {
      if (index < _numSolutions)
        return _solutions[index];
    }
    /**
     * 
     */
    void setSolutions (Solution ** value, unsigned short numSol ) {
        _solutions = value;
	_numSolutions = numSol;
    }
    /** Return the capacity of centers
    */
    double capacity(){
      return _capacity; 
    }
    /** Set the capacity os centers.
    */
    void setCapacity(double value){
	_capacity = value;
    }
     
    /** @brief Return how tight is demands by capacity.
    *
    */
    double tight();
    /**
     * Private stuff
     */
private:
    /**
     * Fields
     */
    unsigned short _numCenters;
    Point ** _points;
    short unsigned int _numPoints;
    CCP::Distance * _distance;
    unsigned short _numSolutions;
    Solution ** _solutions;
    
    double _capacity;

};
}
#endif //INSTANCE_H

