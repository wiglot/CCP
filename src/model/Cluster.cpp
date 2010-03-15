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

#include "Cluster.h"
#include "Instance.h"
#include "Solution.h"
#include "Point.h"
#include <QList>
#include <QDebug>

using namespace CCP;


bool InterchangeResult::undo(){
    if (_valid){
        _valid = false;
        if (_destP == 0){
            return _destC->shift(_origP, _origC).isValid();
        }else{
            return _destC->shift(_origP,_destP, _origC).isValid();
        }
    }
    return false;
}


Cluster::Cluster(Instance* inst): _instance(inst)
{
  this->center = 0;
  points.clear();
}

Cluster::~Cluster(){ }

void Cluster::addPoint(Point* p){
//     _instance->setPointType(p, Consumer);
    if (remainCapacity() < p->demand()){
        qDebug() << "Over capacity inserting Point:" << p->index();
    }
    points.append(p);
}

double Cluster::actualDemand(){
  double totalDemand = 0;
    foreach(Point * i, points){
      totalDemand += i->demand();
    }
    if (center != 0){
        totalDemand += this->center->demand();
    }
    return totalDemand;
}

double Cluster::remainCapacity(){
  return (_instance->capacity() - actualDemand());
}

void Cluster::removePoint(Point * p){
  for (int i = 0; i < points.size(); ++i){
    if (p == points[i]){
        points.removeAt(i);
        return;
    }
  }
}

void Cluster::setCenter(Point * center){
//       if (this->center != 0){
// 	 removePoint(center);
//       }
      //_instance->setPointType(center, Center);
      this->center = center;
//       addPoint(center);
    }

double Cluster::totalDistance(){
  double total = 0.0;
//   Instance * inst = this->_instance->getInstance();

  for (int i = 0; i< points.size(); ++i){
     total += _instance->distance(center, getPoint(i));
  }
  return total;
}

Point * Cluster::getPoint(unsigned short index){
    return points.at(index);
}

Point * Cluster::takePoint( unsigned short  arg1 ){
  Point* candidacte = getPoint(arg1);
  removePoint(candidacte);
  return candidacte;
}

unsigned short int Cluster::numPoints(){
    return points.size();
}

const Cluster Cluster::operator=(const Cluster &other){
    this->center = other.center;
    foreach (Point * p, other.points){
        this->points.append(p);// = other.points;
    }
    this->_instance = other._instance;

    return *this;
}

InterchangeResult Cluster::shift(Point* origPoint, Cluster* dest){
    InterchangeResult result(origPoint, this, 0, dest);
    if (center != origPoint){
        if (dest->remainCapacity() >= origPoint->demand()){
            double newDistance = _instance->distance(origPoint, dest->getCenter());
            double oldDistance = _instance->distance(origPoint, center);

            removePoint(origPoint);
            dest->addPoint(origPoint);

            result.valueChange(newDistance - oldDistance );
            result.valid();
        }
    }
    return result;
}

InterchangeResult Cluster::shift(Point* origPoint, Point* destPoint, Cluster* dest){
    InterchangeResult result(origPoint, this, destPoint, dest);
    if (center != origPoint && destPoint != dest->getCenter()){
        if ((dest->remainCapacity()+destPoint->demand()) >= origPoint->demand()){
            if ((remainCapacity()+origPoint->demand()) >= destPoint->demand()){
                double newDistance = _instance->distance(origPoint, dest->getCenter()) +
                                     _instance->distance(destPoint, center);

                double oldDistance = _instance->distance(origPoint, center) +
                                     _instance->distance(destPoint, dest->getCenter());

                removePoint(origPoint);
                dest->removePoint(destPoint);
                addPoint(destPoint);
                dest->addPoint(origPoint);
                result.valueChange(newDistance - oldDistance);
                result.valid();
            }else{
                qDebug() << "can't Insterchange:" << (remainCapacity()+origPoint->demand()) << destPoint->demand();
            }
        }else{
            qDebug() << "can't Insterchange:" << (dest->remainCapacity()+destPoint->demand()) << origPoint->demand();
        }
    }
    return result;
}
