#ifndef POSITION_H
#define POSITION_H

#include <string>

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

