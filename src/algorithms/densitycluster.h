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

#ifndef DENSITYCLUSTER_H
#define DENSITYCLUSTER_H

#include "algorithmstruct.h"

class DensityCluster:public AlgorithmStruct{
public:
  
    DensityCluster(CCP::Instance* inst);
    ~DensityCluster();
    
    double pointDensity(unsigned short index){
	return this->_pointsDensity[index];
    }
    
    double pointRegret(unsigned short index){
	return this->_pointsRegret[index];
    }
    unsigned short greatDensity(unsigned short big = 0);
    
    unsigned short greatRegret(unsigned short big = 0);
    
    /** @brief find the 'nNeibor' most near from the 'point' that don't over capacity of cluster.
      @param point Origin point.
      @param nNeibor Number of neibors to find.
      @return returnn a list of the neibors.
     */
     QList< int > findNeiborhood(short unsigned int point, unsigned short nNeibor);
     /** @brief calculate the distance from 'point' to all points at 'list'
	 @param point origin point
	 @param list list of points.
	 @return Total distance from point to all list.
     */
//      double distance(short unsigned int point, QList< int > list);

     void calculateDensity();
     
     void setNumIterations(int iter){_iterations = iter;}
     int iterations(){return _iterations;}
     
     CCP::Cluster ** buildClusters();
     
private:
    double * _pointsDensity;
    double * _pointsRegret;
    
    int _iterations;
    
    void calculateRegret(short unsigned int point);
    
    void findBestCluster(short unsigned int clusters);
};

#endif // DENSITYCLUSTER_H
