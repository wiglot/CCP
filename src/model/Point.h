#ifndef POINT_H
#define POINT_H

#include <string>
#include "Position.h"

/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Point
 * 
 */
class Point {
/**
 * Public stuff
 */
public:
    /**
     * Constructors
     */
    /**
     * Empty Constructor
     */
    Point ( );
    Point (double x, double y, double demand);
    Point (Position pos, double demand): _pos(pos), _demand(demand){ }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    CCP::Position position ( ) {
        return _pos;
    }
    /**
     * 
     */
    void setPosition (CCP::Position value ) {
        _pos = value;
    }
    /**
    *
    */
    void setDemand(double value) {
	_demand = value;
    }
    
    double demand(){
	return _demand;
    }
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     CCP::Position _pos;
     double _demand;
};
} 
#endif //POINT_H

