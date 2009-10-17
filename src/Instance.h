#ifndef INSTANCE_H
#define INSTANCE_H

















#include <string>
#include "distance.h"
















/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Instance
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
class Instance {
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
    CCP ( ) { }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    unsigned short get__numCenters ( ) {
        return _numCenters;
    }
    /**
     * 
     */
    void set__numCenters (unsigned short value ) {
        _numCenters = value;
    }
    /**
     * 
     */
    Point * get_points ( ) {
        return points;
    }
    /**
     * 
     */
    void set_points (Point * value ) {
        points = value;
    }
    /**
     * 
     */
    CCP::Distance get_distances ( ) {
        return distances;
    }
    /**
     * 
     */
    void set_distances (CCP::Distance value ) {
        distances = value;
    }
    /**
     * 
     */
    Solution * get__solutions ( ) {
        return _solutions;
    }
    /**
     * 
     */
    void set__solutions (Solution * value ) {
        _solutions = value;
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
     unsigned short _numCenters;
     Point * points;
     CCP::Distance distances;
     Solution * _solutions;
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
#endif //INSTANCE_H

