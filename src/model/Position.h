#ifndef POSITION_H
#define POSITION_H

#include <cmath>

/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Position
 */
class Position {
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
    Position ( ) { }
    Position (double x, double y) {
      _x = x;
      _y = y;
    }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    double x ( ) {
        return _x;
    }
    /**
     * 
     */
    void setX (double value ) {
        _x = value;
    }
    /**
     * 
     */
    double y ( ) {
        return _y;
    }
    /**
     * 
     */
    void setY (double value ) {
        _y = value;
    }
    double distance(const Position p){
      return sqrt((this->_x - p._x)*(this->_x - p._x) + (this->_y - p._y)*(this->_y - p._y));
    }

/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     double _x;
     double _y;
    
};
} 
#endif //POSITION_H

