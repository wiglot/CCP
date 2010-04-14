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
    _demand = 0;
    foreach(Point * i, points){
        _demand += i->demand();
    }
    if (center != 0){
        _demand += this->center->demand();
    }
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

bool Cluster::contains(Point * p){
    if (points.contains(p)){
        return true;
    }
    if (center == p){
        return true;
    }
    return false;
}

Point* Cluster::findBestCenter(){
    double x = 0.0, y = 0.0;
    CCP::Position centroid;
    int count;

    //    Point * oldCenter = center;

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
    QMultiMap <double, Point*> distances;
    foreach (CCP::Point * p, points){
        distances.insert(p->position().distance(centroid), p);
    }
    if (center != 0){
        distances.insert(center->position().distance(centroid), center);
    }
    QMultiMap <double, Point*> betterCenters;

    betterCenters.insert(_distance, center);
    /** seek only for 50% of points */
    for (count = 0; count < (distances.keys().count()*0.3); ++count){
        Point* index = distances.value(distances.keys().at(count));
        double distance = 0.0;
        if (index != center){
            distance += _instance->distance(index->index(), center->index());
        }else{ //Is actual center, no calc needed.
            betterCenters.insert(_distance, index);
            continue;
        }

        foreach(Point* tmp, points){
            if (tmp != index){
                distance += _instance->distance(index->index(), tmp->index());
            }
        }
        betterCenters.insert(distance, index);


    }

    return betterCenters.value(betterCenters.keys().at(0));

}


InterchangeResult Cluster::shift(Point* origPoint, Cluster* dest){
    InterchangeResult result(origPoint, this, 0, dest);
    double newDistance = 0.0;
    double oldDistance = 0.0;
//    if (center != origPoint){
        if (dest->remainCapacity() >= origPoint->demand()){
            oldDistance = totalDistance() + dest->totalDistance();

            if (center == origPoint){
                if (points.count() > 0){
                    setCenter(takePoint(0));
                }else{
                    setCenter(0);
                }
                dest->addPoint(origPoint);
            }else{
                removePoint(origPoint);
                dest->addPoint(origPoint);
            }
            Point *newCenter = findBestCenter();
            if (newCenter != center){
                Point* p = center;
                removePoint(newCenter);
                setCenter(newCenter);
                addPoint(p);
            }
            newCenter = dest->findBestCenter();
            if (newCenter != dest->getCenter()){
                Point* p = dest->getCenter();
                dest->removePoint(newCenter);
                dest->setCenter(newCenter);
                dest->addPoint(p);
            }
            newDistance = totalDistance() + dest->totalDistance();
            result.valueChange(newDistance - oldDistance );
            result.valid();
        }
//    }
    return result;
}

InterchangeResult Cluster::interchange(Point* origPoint, Point* destPoint, Cluster* dest){
    InterchangeResult result(origPoint, this, destPoint, dest);
    double newDistance = 0.0;
    double oldDistance = 0.0;

    //    if (center != origPoint && destPoint != dest->getCenter()){

    if ((dest->remainCapacity()+destPoint->demand()) >= origPoint->demand()){
        if ((remainCapacity()+origPoint->demand()) >= destPoint->demand()){
            oldDistance = totalDistance() + dest->totalDistance();
            if (center == origPoint){
                dest->removePoint(destPoint);
                setCenter(destPoint);
                dest->addPoint(origPoint);
            }else if (dest->getCenter() == destPoint){
                removePoint(origPoint);
                dest->setCenter(origPoint);
                addPoint(destPoint);
            }else {
                removePoint(origPoint);
                dest->removePoint(destPoint);
                addPoint(destPoint);
                dest->addPoint(origPoint);
            }
            Point *newCenter = findBestCenter();
            if (newCenter != center){
                Point* p = center;
                removePoint(newCenter);
                setCenter(newCenter);
                addPoint(p);
            }
            newCenter = dest->findBestCenter();
            if (newCenter != dest->getCenter()){
                Point* p = dest->getCenter();
                dest->removePoint(newCenter);
                dest->setCenter(newCenter);
                dest->addPoint(p);
            }
            newDistance = totalDistance() + dest->totalDistance();
            result.valueChange(newDistance - oldDistance);
            result.valid();
        }/*else{
                qDebug() << "can't Insterchange:" << (remainCapacity()+origPoint->demand()) << destPoint->demand();
            }*/
    }/*else{
            qDebug() << "can't Insterchange:" << (dest->remainCapacity()+destPoint->demand()) << origPoint->demand();
        }*/

    return result;
}
