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

#ifndef ALGORITHMSTRUCT_H
#define ALGORITHMSTRUCT_H

#include "../model/model_global.h"
#include <QList>
#include <QObject>
#include "../model/Instance.h"
#include "../model/Solution.h"
#include "../model/Cluster.h"

/** @class AlgorithmStruct
    @brief A helper class that take care of know if a point is assigned or not, and some operations needed by various methods.
    
*/
class AlgorithmStruct:public QObject {
Q_OBJECT
protected:    
  CCP::Instance * _myInstance;
  int * _assigned;
  CCP::PointType * _pointType;
  CCP::Cluster ** _centers;
  int _iterations;

signals:
  void complete(int percentage);
public:
    AlgorithmStruct(CCP::Instance * inst);
    ~AlgorithmStruct(){
	delete [] _assigned;
    }
    
    int incIter();

    int iterations(){ return _iterations; }

    inline CCP::Instance * instance(){return _myInstance;}
    CCP::Cluster * cluster(int index){return _centers[index];}
    CCP::PointType pointType(int index);
//     inline void setPointType(unsigned short point, CCP::PointType type){
// 	_pointType[point] = type;
//     }
    inline bool isAssigned(unsigned short index){
      return (this->assignedTo(index) != -1);
    }
    
    inline int assignedTo(unsigned short index){
	return this->_assigned[index];
    }
    
    void assign(unsigned short point, int cluster, CCP::PointType asType = CCP::Consumer);
    void assign(CCP::Point * point, int cluster, CCP::PointType asType = CCP::Consumer);
    void unAssign(CCP::Point * point);
    void unAssign(unsigned short index);
    
    void unAssignAllConsumers();
    


    /** @brief calculate the distance from 'center' to all points on list 'points'.
    */
    double distance(unsigned short center, QList<int> points);
    
    /** @brief seek for wich is the best center of clusters.
    */
    bool findBestCenters(short unsigned int numClusters = 0);
    
    
    /** @brief Find a center near of \point excluding centers in \forbiden
    Return center(cluster) index or -1 if there is no centers was found. Capacity is not take in consideration here.
    */
    int findNearCenter(CCP::Point* point, QList< int > forbiden);

    /** @brief Assign all not yet assigned points to near center.

    */
    void assignToNearest();
    
    virtual CCP::Cluster** buildClusters() = 0;
};

#endif // ALGORITHMSTRUCT_H
