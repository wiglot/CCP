#ifndef POSITION_H
#define POSITION_H

















#include <string>

















/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Position
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
class Position {
/**
 * Public stuff
 */
public:
    /**
     * Fields
     */
    /**
     * 
     */
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
    double get__x ( ) {
        return _x;
    }
    /**
     * 
     */
    void set__x (double value ) {
        _x = value;
    }
    /**
     * 
     */
    double get__y ( ) {
        return _y;
    }
    /**
     * 
     */
    void set__y (double value ) {
        _y = value;
    }
/**
 * Protected stuff
 */
protected:
    /**
     * Fields
     */
    /**
     * 
     */
    /**
     * Constructors
     */
    /**
     * Accessor Methods
     */
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     double _x;
     double _y;
    /**
     * 
     */
    /**
     * Constructors
     */
    /**
     * Accessor Methods
     */
};
} 
#endif //POSITION_H

