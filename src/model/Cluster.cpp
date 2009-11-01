/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "Cluster.h"
#include "Instance.h"
#include "Solution.h"
#include "Point.h"
#include <QList>

CCP::Cluster::Cluster(Solution* inst): solution(inst)
{ 
  this->center = 0;
}

CCP::Cluster::~Cluster(){ }

void CCP::Cluster::addPoint(CCP::Point* p){
    points.append(p);
}

double CCP::Cluster::actualDemand(){
  double totalDemand = 0;
    foreach(Point * i, points){
      totalDemand += i->demand();
    }
    totalDemand += this->center->demand();
    return totalDemand;
}

double CCP::Cluster::remainCapacity(){
  return (solution->getInstance()->capacity() - actualDemand());
}

void CCP::Cluster::removePoint(Point * p){
  for (int i = 0; i < points.size(); ++i){
    if (p == points[i]){
	points.removeAt(i);
	return;
    }
  }
}

double CCP::Cluster::totalDistance(){
  double total = 0.0;
  Instance * inst = this->solution->getInstance();
  for (int i = 0; i< points.size(); ++i){
     total += inst->distance(center, points.at(i));
  }
  return total;
}

CCP::Point * CCP::Cluster::getPoint(unsigned short index){
    return points.at(index);
}

CCP::Point * CCP::Cluster::takePoint( unsigned short  arg1 ){
  Point* candidacte = getPoint(arg1);
  removePoint(candidacte);
  return candidacte;
}

unsigned short int CCP::Cluster::numPoints(){
    return points.size();
}