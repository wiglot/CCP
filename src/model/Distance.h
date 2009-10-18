#ifndef DISTANCE_H
#define DISTANCE_H

#include <string>

/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Distance
 * Contains the values of distances, will be build empty, and at every request, it will build the matrix and vectors(ordered) of distances  
 */
class Distance {
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
    Distance ( ) { }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    double get__values ( ) {
        return _values;
    }
    /**
     * 
     */
    void set__values (double value ) {
        _values = value;
    }
private:
    /**
     * Fields
     */
     double _values;

};
} 
#endif //DISTANCE_H

