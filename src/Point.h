#ifndef POINT_H
#define POINT_H














#include <string>
#include "position.h"
















/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Point
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
class Point {
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
    Point ( ) { }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    CCP::Position get__pos ( ) {
        return _pos;
    }
    /**
     * 
     */
    void set__pos (CCP::Position value ) {
        _pos = value;
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
     CCP::Position _pos;
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
#endif //POINT_H

