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

#include "algorithmstruct.h"
#include "Instance.h"

using namespace CCP;


AlgorithmStruct::AlgorithmStruct( Instance* inst ):
  _myInstance(inst)
{
  _assigned = new int[_myInstance->numPoints()];
  this->_centers = new Cluster*[_myInstance->numCenters()];
  for (unsigned short count = 0 ; count < _myInstance->numCenters(); ++count){
      this->_centers[count] = new Cluster(_myInstance);
  }
  for (unsigned short count = 0; count < _myInstance->numPoints(); ++count){
    this->_assigned[count] = -1;
  }
}

CCP::PointType AlgorithmStruct::pointType(int index){
    for (unsigned short i = 0; i < _myInstance->numCenters(); ++i){
	if (_centers[i]->getCenter() == _myInstance->point(index))
	    return CCP::Center;
    }
    return CCP::Consumer;
}

double AlgorithmStruct::distance(unsigned short point, QList <int> list){
    double acum = 0.0;
    foreach(int i, list){
	acum += _myInstance->distance(i, point);
    }
    return acum;
}

void AlgorithmStruct::assign(CCP::Point * point, int cluster, CCP::PointType asType){
    assign(_myInstance->pointIndex(point), cluster, asType);
}

void AlgorithmStruct::assign(unsigned short point, int cluster, CCP::PointType asType){
	if (assignedTo(point) != -1){
	    unAssign(point);
	}
	this->_assigned[point] = cluster;
	if (asType == CCP::Center){
	    _centers[cluster]->setCenter(_myInstance->point(point));
	}else{
	    _centers[cluster]->addPoint(_myInstance->point(point));
	}
    }
    
void AlgorithmStruct::unAssign(unsigned short index){
    if (pointType(index) == CCP::Center){
	this->_centers[this->_assigned[index]]->setCenter(0);
    }else{
	this->_centers[this->_assigned[index]]->removePoint(_myInstance->point(index));
    }
    this->_assigned[index] = -1;
}