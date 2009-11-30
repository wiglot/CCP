/*
    CCP - Capacited Clustering Problem.
    Copyright (C) 2009  Wagner Reck (wagner.reck@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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
    Distance (CCP::Instance* inst);
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
    short unsigned int near ( short unsigned int arg1, short unsigned int nearest );
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
      int ** _near;

      /**
      */
      double distanceBetween ( short unsigned int arg1, short unsigned int arg2 );

};
} 
#endif //DISTANCE_H

