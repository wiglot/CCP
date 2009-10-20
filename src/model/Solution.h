#ifndef SOLUTION_H
#define SOLUTION_H

/**
 * Namespace
 */

namespace CCP {
class Instance; 

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
    Solution ( ) { }
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
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */

     Instance * _myInstance;
     PointType * _pointsType;
     unsigned short * _centersIndex;
     
    void selectFirstCenters();
    void findBasicClusters();
};
} 
#endif //SOLUTION_H

