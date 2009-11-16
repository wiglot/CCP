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

#ifndef SOLUTION_H
#define SOLUTION_H

/**
 * Namespace
 */
#include "Point.h"
#include <QList>

namespace CCP {
  class Point;
class Instance; 
class Cluster;

enum PointType {
  Center,
  Consumer
};

enum HeuristicType {
  Density,
  Farthest
};
/**
 * Class Solution
 */
class Solution {
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
    Solution ( Instance * instance);
    
    ~Solution();
    /**
     * Accessor Methods
     */
    /** 
    */
    void setInstance (Instance * inst);
    
    /**
    *
    */
    Instance * instance(){
      return _myInstance;
    }
    /**
     * 
     */
    PointType pointType (unsigned short index);


//     void setPointsType (PointType * value ) {
//         _pointsType = value;
//     }
    
    void constructSolution(HeuristicType type = CCP::Farthest);
    
    
    
    Cluster * cluster(unsigned short index){
	return _centers[index];
    }
    
    /**
     * @brief Return the point thats represent the center of cluster at index.
     * Use this method is same that does Solution::cluster(index)->centerPoint();
     * @param index index of cluster in array. Shoud be less than number of centers.
     * @return Point considered as center os cluster.
    */
    Point centerOfCluster(unsigned short index);
    Instance * getInstance(){
      return _myInstance;
    }
    double getValue();
    void setPointType( Point* arg1, PointType arg2 );
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */

     Instance * _myInstance;
//      PointType * _pointsType;
     Cluster ** _centers;
     
     
     /** some only private use methods
     */

     
    
};
} 
#endif //SOLUTION_H

