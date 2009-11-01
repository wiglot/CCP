#ifndef SOLUTION_H
#define SOLUTION_H

/**
 * Namespace
 */
#include "Point.h"

namespace CCP {
  class Point;
class Instance; 
class Cluster;

enum PointType {
  Center,
  Consumer
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
    PointType pointType (unsigned short index) {
        return _pointsType[index];
    }
    /**
     * 
     */
    void setPointsType (PointType * value ) {
        _pointsType = value;
    }
    
    void constructSolution();
    
    void findBestCenters();
    
    Cluster cluster(unsigned short index);
    
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
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */

     Instance * _myInstance;
     PointType * _pointsType;
     Cluster ** _centers;
     
     
     /** some only private use methods
     */
     void selectFirstCenters();
     void findBasicClusters();
    
};
} 
#endif //SOLUTION_H

