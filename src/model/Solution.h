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
#include <QObject>
#include <QList>
#include <QString>
#include <QMutex>
#include <QThread>

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
  Farthest,
  HMeans,
  JMeans
};
/**
 * Class Solution
 */
class Solution{
//    :public QObject {
//    Q_OBJECT
/**
 * Public stuff
 */
//public slots:


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

    
    void constructSolution(HeuristicType type);
    


    void setAlgorithmToUse(HeuristicType type);


    void run();


    Cluster * cluster(unsigned short index){
	return _centers[index];
    }
    
    /** return name of algorithm used.*/
    QString algorithmName(){ return _myAlgorithmName;}

    /** Return time taken to perform selected algorithm (in seconds).*/
    double timeTaken(){return _myTime;}

    /** Return iterations taken to perform algorithm. */
    long iterations(){return _myIterations;}

    /**
     * @brief Return the point thats represent the center of cluster at index.
     * Use this method is same that does Solution::cluster(index)->centerPoint();
     * @param index index of cluster in array. Shoud be less than number of centers.
     * @return Point considered as center os cluster.
    */
    Point * centerOfCluster(unsigned short index);
    Instance * getInstance(){
        return _myInstance;
    }
    double getValue();
    void setPointType( Point* arg1, PointType arg2 );
    
    /** @brief Return if the Solution is valid or not.
	This method check if all points are assigned to only on cluster, all cluster have a center and the center is not an consumer point too.
	Is checked also the capacity of clusters.
	*/
    const bool isValid();

    const bool isRunnig(){
        if (_lock.tryLock()){
            _lock.unlock();
            return false;
        }
        return true;
    }

//     Solution & operator=(const Solution & other);

//signals:
//    void finished();
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     long _myIterations;
     double _myTime;
     QString _myAlgorithmName;

     Instance * _myInstance;
//      PointType * _pointsType;
     Cluster ** _centers;
     
     HeuristicType _type;


     QMutex _lock;
     /** some only private use methods
     */

     
    
};
} 
#endif //SOLUTION_H

