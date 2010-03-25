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
//#include <QMultiMap>
#include <QDebug>

using namespace CCP;


bool InterchangeResult::undo(){
    if (_valid){
        _valid = false;
        _canRedo = true;
        if (_destP == 0){
            return _destC->shift(_origP, _origC).isValid();
        }else{
            return _destC->interchange(_origP,_destP, _origC).isValid();
        }
    }
    return false;
}

bool InterchangeResult::redo(){
    if (_canRedo){

        _valid = true;
        _canRedo = false;
        if (_destP == 0){
            return _origC->shift(_origP, _destC).isValid();
        } else {
            return _origC->interchange(_origP, _destP, _destC).isValid();
        }
        return true;
    }
    return false;

}
//const InterchangeResult & operator=(const InterchangeResult & other){
//    _valid = other._valid;
//    _canRedo = other._canRedo;
//    _change = _CHAR_TRAITS_H;
//    _origP = origPoint;
//    _destP = destPoint;
//    _destC = destCluster;
//    _origC = origCluster;
//}

Cluster::Cluster(Instance* inst): _instance(inst)
{
  this->center = 0;
  _distance = 0.0;
  _demand = 0.0;
  points.clear();
}

Cluster::~Cluster(){ }

void Cluster::addPoint(Point* p){
//     _instance->setPointType(p, Consumer);
    if (remainCapacity() < p->demand()){
        qDebug() << "Over capacity inserting Point:" << p->index();
    }
    points.append(p);
    _demand += p->demand();
    if (center != 0)
        _distance += _instance->distance(p, center);
}

double Cluster::actualDemand(){
//  double totalDemand = 0;
//    foreach(Point * i, points){
//      totalDemand += i->demand();
//    }
//    if (center != 0){
//        totalDemand += this->center->demand();
//    }
    return _demand;
}

double Cluster::remainCapacity(){
  return (_instance->capacity() - actualDemand());
}

void Cluster::removePoint(Point * p){
    points.removeOne(p);
    _demand -= p->demand();
    if (center != 0)
        _distance -= _instance->distance(p, center);
//  for (int i = 0; i < points.size(); ++i){
//    if (p == points[i]){
//        points.removeAt(i);
//        return;
//    }
//  }
}

void Cluster::setCenter(Point * c){
       if (this->center != 0){
           _demand -= center->demand();
       }
      //_instance->setPointType(center, Center);
      this->center = c;

      if (center == 0) {
          return ;
      }

      _demand += center->demand();

      _distance = 0.0;
      foreach (Point *p, points){
          _distance += _instance->distance(p, center);
      }
    }

double Cluster::totalDistance(){
  return _distance;
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
    this->_instance = other._instance;

    this->setCenter(other.center);
    foreach (Point * p, other.points){
        this->addPoint(p);// = other.points;
    }

    return *this;
}

bool Cluster::findBestCenter(){
    double x = 0.0, y = 0.0;
    CCP::Position centroid;
    int count;

    foreach (CCP::Point * p, points){
        x += p->position().x();
        y += p->position().y();
    }

    if (center != 0){
        x += center->position().x();
        y += center->position().y();

        centroid.setX( x/ (points.count() + 1.0) );
        centroid.setY( y/ (points.count() + 1.0) );
    }else{ //Don't have a center yet.
        centroid.setX( x/ (points.count()) );
        centroid.setY( y/ (points.count()) );
    }
    QMultiMap <double, int> distances;
    foreach (CCP::Point * p, points){
        distances.insert(p->position().distance(centroid), points.indexOf(p));
    }
    if (center != 0){
        distances.insert(center->position().distance(centroid), -1);
    }
    QMultiMap <double, int> betterCenters;

    /** seek only for 50% of points */
    for (count = 0; count < (points.count()/2 ); ++count){
        int index = distances.value(distances.keys().at(count));
        double acum = 0.0;
        foreach (CCP::Point *p, points){
            if (index == -1){
                acum += p->position().distance(center->position());
            }else{
                acum += p->position().distance(points.at(index)->position());
            }
        }
        if (center != 0){
            if (index != -1){
                acum += center->position().distance(points.at(index)->position());
            }
        }
        betterCenters.insert(acum, index);
    }
    if (count != 0){
        if (betterCenters.value(betterCenters.keys().at(0)) == -1){
            return false;
        } else {
            Point * p = center;
            setCenter(takePoint(betterCenters.value(betterCenters.keys().at(0))));
            addPoint(p);

            return true;
        }

    }
    return false;
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

InterchangeResult Cluster::interchange(Point* origPoint, Point* destPoint, Cluster* dest){
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
            }/*else{
                qDebug() << "can't Insterchange:" << (remainCapacity()+origPoint->demand()) << destPoint->demand();
            }*/
        }/*else{
            qDebug() << "can't Insterchange:" << (dest->remainCapacity()+destPoint->demand()) << origPoint->demand();
        }*/
    }
    return result;
}
