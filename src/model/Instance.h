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

#ifndef INSTANCE_H
#define INSTANCE_H

#include "model_global.h"

#include <string>
#include <QString>
#include "Distance.h"
#include "Point.h"

namespace CCP {

class Solution;
/**
 * Class Instance
 */
class CCPModelLib_EXPORT Instance {
    /**
     * Public stuff
     */
public:
    /**
     * Empty Constructor
     */
    Instance ( ) {
      setNumCenters(0);
      setPoints(0, 0);
      setName("default");
      setDistances(0);
    }
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
    void setPoints (Point ** value, unsigned short numPoints);
    /**
    * Overloaded function, same that instance::distancesMatrixes()->distance(p1, p2)
    */
    double distance (unsigned short p1, unsigned short p2, double factor = 1);
    
    
    double distance (Point * p1, Point * p2, double factor = 1);
    /**
     *
     */
    CCP::Distance * distancesMatrixes ( ) {
        if (_distance == 0){
            new CCP::Distance(this);
        }

        //throw QString ("Initialize \"Distance\" First.");
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
//     Solution * solutions ( unsigned short index) {
//       if (index < _numSolutions)
//         return _solutions[index];
//     }
    /**
     * 
     */
//     void setSolutions (Solution ** value, unsigned short numSol ) {
//         _solutions = value;
// 	_numSolutions = numSol;
//     }
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
    
    void setName( QString arg1 ){
      _name = arg1;
    }
    QString name(){return _name;}
    unsigned short pointIndex( Point* arg1 );
    void arg( short unsigned int arg1 );
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
//     unsigned short _numSolutions;
//     Solution ** _solutions;
    
    double _capacity;
    QString _name;

};
}
#endif //INSTANCE_H

