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



DensityCluster::DensityCluster(Instance* inst): AlgorithmStruct(inst)
{
    this->_pointsDensity = new double[this->instance()->numPoints()];
    this->_pointsRegret = new double[instance()->numPoints()];
    
    for (unsigned short i = 0; i < instance()->numPoints(); ++i){
      this->_pointsDensity[i] = -1.0;
      this->_pointsRegret[i] = -1.0;
    }
    setNumIterations(10);
}


DensityCluster::~DensityCluster() {
  delete []_pointsDensity;
  delete []_pointsRegret;
}

// double DensityCluster::distance(short unsigned int point, QList< int > list)
// {
//   return 0.0;
// }


CCP::Cluster ** DensityCluster::buildClusters(){

    unsigned short numNeibor = instance()->numPoints() / instance()->numCenters();
//   para k = 1 até p faça
//   	Para todo ponto não atribuido
//       	Calcule os vizinhos e a densidade
//   	ordene em ordem decrescente as densidades
//   	ponto com maior densidade será o kº centro.
//   	atribua os vizinhos a kº centro.
//   	if k >= 2
//       	Find_Best_Clusters(Centros, Pontos_Atribuidos)
//   Find_Best_Clusters(Centros, Todos_Pontos)
    for (unsigned short count = 0; count < _myInstance->numCenters(); count++){
	this->calculateDensity();
	unsigned short tmp = this->greatDensity();
	
	QList <int> neibor = this->findNeiborhood(tmp, numNeibor);
	
	assign(tmp, count, CCP::Center);
	this->_pointsDensity[tmp] = 0.0; 
		
	foreach(int actual, neibor){
	    if (_myInstance->point(actual) != cluster(count)->getCenter()){
	      assign(actual, count);
	      this->_pointsDensity[actual] = 0.0; 
	    }
	}
	if (count > 0){
	    findBestCluster(count+1);
	}
    }
    findBestCluster(_myInstance->numCenters());
    return this->_centers;
    
}

void DensityCluster::findBestCluster(unsigned short clusters){
 unsigned short iter = 0, i, j;
 bool change = true;
 unsigned short nearCenter, nextPoint;
 
 while (iter < _iterations && change){
    change = false;
    ++iter;
    //Reassing!!
    //unassing all points!
    QList <unsigned short> unAssgned;
    for (i = 0 ; i < clusters; i++){
	unsigned short tmp = cluster(i)->numPoints();
	for (j = 0; j < tmp; j++){
	    unAssgned.append(instance()->pointIndex( cluster(i)->getPoint(0)));
	    unAssign(cluster(i)->getPoint(0));
	}
    }
    //For each point unassigned
    while (unAssgned.size() > 0){
      double maxRegret = -1.0;
      foreach(i, unAssgned){
	  calculateRegret(i);
	  if (maxRegret < pointRegret(i)){
	      nextPoint = i;
	      maxRegret = pointRegret(i);
	  }
      }
//       //select the great regret
//       i = 0;
//       do {
// 	nextPoint = this->greatRegret(i);
// 	++i;
//       } while (isAssigned(nextPoint) && i < instance()->numPoints()); //never select a assigned point.
      //Find the near center
      
      double min = 1.0e10;
      
      for (i = 0; i < clusters; ++i){
	    if (cluster(i)->remainCapacity() >= instance()->point(nextPoint)->demand()){
		if (instance()->distance(cluster(i)->getCenter(), instance()->point(nextPoint)) < min){
		    min = instance()->distance(cluster(i)->getCenter(), instance()->point(nextPoint));
		    nearCenter = i;
		}
	    }
      }
      
      assign(nextPoint, nearCenter);
      this->_pointsRegret[nextPoint] = -1.0;
      unAssgned.removeOne(nextPoint);
    }
    //	ca
    //update centers
    change = this->findBestCenters(clusters);
    
 }
   
}

void DensityCluster::calculateDensity(){

    unsigned short m;
    QList <int>  neibors;
    
    m = instance()->numPoints() / instance()->numCenters();
    for (unsigned short i = 0; i < instance()->numPoints(); ++i){
	if (! this->isAssigned(i)){
	  neibors = this->findNeiborhood(i, m);
	  _pointsDensity[i] = (double)neibors.size()/this->distance(i, neibors);
	}
    }
}

void DensityCluster::calculateRegret(unsigned short point){
//     unsigned short * tmpCenters = new unsigned short[instance()->numCenters()];
    unsigned short count2;
    double distance1, distance2;
    unsigned short center1, center2;
    Point * p = instance()->point(point);
//     what hell is this!!
//     for (count = 0; count < instance()->numCenters(); ++count){
// 	tmpCenters[count] = this->greatDensity(count);
//     }
    center1 = center2 = instance()->numPoints();
	distance1 = 1.0e10;
	distance2 = 1.0e10;
	for (count2 = 0; count2 < instance()->numCenters(); ++count2){
	      if (cluster(count2)->getCenter() != 0){
		if (instance()->distance(p, cluster(count2)->getCenter()) < distance1){
		    distance1 = instance()->distance(p, cluster(count2)->getCenter());
		    center1 = count2;
		}
	      }
	}
	for (count2 = 0; count2 < instance()->numCenters(); ++count2){
	      if (cluster(count2)->getCenter() != 0){
		if (instance()->distance(p, cluster(count2)->getCenter()) < distance2 && count2 != center1){
		    distance2 = instance()->distance(p, cluster(count2)->getCenter());
		    center2 = count2;
		}
	      }
	}
	if (center1 < instance()->numPoints() && center2 < instance()->numPoints()){
	  this->_pointsRegret[point] = distance2 - distance1;
	}
//     }
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
	  if (! isAssigned(p)){
	    if ((instance()->point(p)->demand()+acumDemand) < instance()->capacity()) {
		acumDemand += instance()->point(p)->demand();
		list.append(p);
		inserted = true;
	    }
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
   found = 0;
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