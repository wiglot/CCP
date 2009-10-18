#ifndef DISTANCE_H
#define DISTANCE_H

/**
 * Namespace
 */
namespace CCP {
  class Instance; 
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
    Distance (Instance * inst);
    ~Distance();
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    inline double distance(unsigned short point1, unsigned short point2 ) {
	if (point1 == point2){
	  return 0.0;
	}if (point1 > point2){
	  if (_values [point1][point2] == -1){
	    _values [point1][point2] = distanceBetween(point1, point2);
	  }
	  return _values [point1][point2];
	}else{
	  if (_values [point2][point1] == -1){
	    _values [point2][point1] = distanceBetween(point1, point2);
	  }
	  return _values [point2][point1];
	}
    }
    /**
     * 
     */
//     void set__values (double value ) {
//         _values = value;
//     }
private:
    /**
     * Fields
     */
    
      Instance * _instance;
      unsigned short _numPoints;
      double ** _values;
      short ** _ordered;

      /**
      */
      double distanceBetween ( short unsigned int arg1, short unsigned int arg2 );

};
} 
#endif //DISTANCE_H

