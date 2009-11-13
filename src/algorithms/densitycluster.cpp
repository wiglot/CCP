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

#include "densitycluster.h"
#include "Distance.h"


using namespace CCP;

void DensityCluster::calculateDensity(){
    this->_pointsDensity = new double[this->instance()->numPoints()];
    unsigned short m;
    QList <int>  neibors;
    
    m = instance()->numPoints() / instance()->numCenters();
    for (unsigned short i = 0; i < instance()->numPoints(); ++i){
	neibors = this->findNeiborhood(i, m);
	_pointsDensity[i] = (double)neibors.size()/this->distance(i, neibors);
	
    }
}

void DensityCluster::calculateRegret(){
    unsigned short * tmpCenters = new unsigned short[instance()->numCenters()];
    unsigned short count, count2;
    double distance1, distance2;
    unsigned short center1, center2;
    this->_pointsRegret = new double[instance()->numPoints()];
    
    for (count = 0; count < instance()->numCenters(); ++count){
	tmpCenters[count] = this->greatDensity(count);
    }
    for (count = 0; count < instance()->numPoints(); ++count){
	distance1 = 1.0e10;
	distance2 = 1.0e10;
	for (count2 = 0; count2 < instance()->numCenters(); ++count2){
	      if (instance()->distance(count, tmpCenters[count2]) < distance1){
		  distance1 = instance()->distance(count, tmpCenters[count2]);
		  center1 = tmpCenters[count2];
	      }
	}
	for (count2 = 0; count2 < instance()->numCenters(); ++count2){
	      if (instance()->distance(count, tmpCenters[count2]) < distance2 && tmpCenters[count2] != center1){
		  distance2 = instance()->distance(count, tmpCenters[count2]);
		  center2 = tmpCenters[count2];
	      }
	}
	this->_pointsRegret[count] = instance()->distance(count, center2) - instance()->distance(count, center1);
    }
}


QList < int >  DensityCluster::findNeiborhood(unsigned short point, unsigned short nNeibor){
    QList<int> list;
    double acumDemand = 0.0;
    unsigned short tmp = 0;
    bool inserted;
    unsigned short p;
    Distance * distance = instance()->distancesMatrixes();
    for (unsigned short i = 0; i < nNeibor; ++i){
	inserted = false;
	do{
	  
	  p = distance->near(point, tmp);
	  if ((instance()->point(p)->demand()+acumDemand) < instance()->capacity()) {
	      acumDemand += instance()->point(p)->demand();
	      list.append(p);
	      inserted = true;
	  }
	  ++tmp;
	}while (!inserted && tmp < instance()->numPoints());
    }
    
    return list;
}


unsigned short DensityCluster::greatRegret(unsigned short big){
    bool * visited = new bool[instance()->numPoints()];
    unsigned short i, count, found;
    double min;

    ++big;

    for ( i = 0; i < instance()->numPoints(); ++i ){
        visited[i] = false;
    }
    
    for ( i = 0 ; i < big; ++i ){
        min = 0.0;
        for ( count = 0; count < instance()->numPoints(); count++ ) {
            if ( !visited[count] )
            {
                if ( pointRegret(count) > min ) {
                    min = pointRegret(count);
                    found = count;
                }
            }
        }
        visited[found] = true;
    }
    delete [] visited;
    return found;
  
}

unsigned short DensityCluster::greatDensity(unsigned short big){
    bool * visited = new bool[instance()->numPoints()];
    unsigned short i, count, found;
    double min;

    ++big;

    for ( i = 0; i < instance()->numPoints(); ++i )
    {
        visited[i] = false;
    }
//     visited[point] = true;
    
    for ( i = 0 ; i < big; ++i )
    {
        min = 0.0;
        for ( count = 0; count < instance()->numPoints(); count++ ) {
            if ( !visited[count] )
            {
                if ( pointDensity(count) > min ) {
                    min = pointDensity(count);
                    found = count;
                }
            }
        }
        visited[found] = true;
    }
    delete [] visited;
    return found;
  
}