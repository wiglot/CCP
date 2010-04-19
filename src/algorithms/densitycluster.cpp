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

#include <cmath>
#include <QDebug>
using namespace CCP;



DensityCluster::DensityCluster(Instance* inst): AlgorithmStruct(inst)
{
    setNumIterations(10);

    _numNeibor = floor( instance()->numPoints() / double(instance()->numCenters())) ;
}


DensityCluster::~DensityCluster() {


}



CCP::Cluster ** DensityCluster::buildClusters(){

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
        _pointsDensity.clear();
        emit complete(int(((count+1)/_myInstance->numCenters())*100));

        this->calculateDensity();

        int tmp = this->greatDensity(); //redo this function and regret.
        if (tmp == -1){
            qDebug() << "Xii... need more points to be the center.";

        }
        // TMP value is overbounding num points at count 39 and 10 iterations
        QList <int> neibor = this->findNeiborhood(tmp, _numNeibor);

        assign(tmp, count, CCP::Center);
        //        this->_pointsDensity[tmp] = 0.0;

        foreach(int actual, neibor){
            if (_myInstance->point(actual) != cluster(count)->getCenter()){
                if (cluster(count)->remainCapacity() >= _myInstance->point(actual)->demand()){
                    assign(actual, count);
                }else{
                    qDebug() << "Can't assign point" << actual << _myInstance->point(actual)->demand();
                }

            }
        }
        if (count > 0){
            findBestCluster(count+1);
        }
    }


    QList<int> assignedPoints;

    for (unsigned short count = 0; count < _myInstance->numPoints(); ++count){
        if (!isAssigned(count)){
            assignedPoints.append(count);
        }
    }

    findBestCluster(_myInstance->numCenters(), assignedPoints);



    return this->_centers;
    
}

void DensityCluster::findBestCluster(unsigned short clusters, QList<int> points){
    unsigned short iter = 0, i, j;
    bool change = true;
    int nearCenter, nextPoint;

    QList <int> unAssgned = points;

    while (iter < _iterations && change){
        change = false;
        ++iter;

        //unassing all points!
        for (i = 0 ; i < clusters; i++){
            unsigned short tmp = cluster(i)->numPoints();
            for (j = 0; j < tmp; j++){
                unAssgned.append(instance()->pointIndex( cluster(i)->getPoint(0)));
                unAssign(cluster(i)->getPoint(0));
            }
        }

        //For each point unassigned

        //Aqui está a demora. Pensar em uma forma melhor.

        while (unAssgned.size() > 0){
            //double maxRegret = -1.0;
            //            foreach(i, unAssgned){
            calculateRegret(unAssgned);
            nextPoint = _pointsRegret.values().back();


            double min = 1.0e10;
            nearCenter = -1;

            for (i = 0; i < clusters; ++i){
                if (cluster(i)->remainCapacity() >= instance()->point(nextPoint)->demand()){
                    if (instance()->distance(cluster(i)->getCenter(), instance()->point(nextPoint)) < min){
                        min = instance()->distance(cluster(i)->getCenter(), instance()->point(nextPoint));
                        nearCenter = i;
                    }
                }
            }
            if (nearCenter != -1){
                assign(nextPoint, nearCenter);
                this->_pointsRegret[nextPoint] = -1.0;

            }else{
                qDebug() << "Cannot insert point:" << nextPoint << "demand:" << instance()->point(nextPoint)->demand();
            }
            unAssgned.removeOne(nextPoint);
        }
        //	ca
        //update centers
        change = this->findBestCenters(clusters);

    }

}

void DensityCluster::calculateDensity(){


    QList <int>  neibors;
    
    for (unsigned short i = 0; i < instance()->numPoints(); ++i){
        if (! this->isAssigned(i)){
            neibors = this->findNeiborhood(i, _numNeibor);
            _pointsDensity.insert((double)neibors.size()/this->distance(i, neibors) , i);
        }
    }
}

void DensityCluster::calculateRegret(QList <int> points){

    unsigned short count2;
    double distance1, distance2;
    unsigned short center1, center2;
    unsigned short numClusters;
    _pointsRegret.clear();
    foreach (int point, points){
        Point * p = instance()->point( point );


        center1 = center2 = instance()->numPoints();

        for (numClusters = 0; numClusters < instance()->numCenters(); ++numClusters){
            if ( cluster( numClusters )->getCenter() == 0 ) {
                break;
            }
        }


        distance1 = 1.0e10;
        distance2 = 1.0e10;
        for ( count2 = 0; count2 < numClusters; ++count2 ) {
            double dist = instance()->distance( p->index(), cluster( count2 )->getCenter()->index() );
            if ( dist < distance1  && p->demand() <= cluster(count2)->remainCapacity()) {
                if (distance1 < distance2){
                    distance2 = distance1;
                    center2 = center1;
                }
                distance1 = dist;
                center1 = count2;
            }
            if (count2 != center1){
                if (dist < distance2 && p->demand() <= cluster(count2)->remainCapacity()){
                    distance2 = dist;
                    center2 = count2;
                }
            }

        }

        this->_pointsRegret.insert(distance2 - distance1, point);

    }
}


QList < int >  DensityCluster::findNeiborhood(unsigned short point, unsigned short nNeibor){
    QList<int> list;
    double acumDemand = 0.0;
    unsigned short tmp = 0;
    bool inserted;
    unsigned short p;
    Distance * distance = instance()->distancesMatrixes();
    for (unsigned short i = 0; i < nNeibor && tmp < instance()->numPoints(); ++i){
        inserted = false;
        do{
            /** BUG Visited point 2000, but only have 422 */
            /** Again SJC4b. point 2053*/
            p = distance->near(point, tmp);
            if (! isAssigned(p)){
                if ((instance()->point(p)->demand()+acumDemand) <= instance()->capacity()) {
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


int DensityCluster::greatRegret(){
    if ( ! _pointsRegret.isEmpty()){
        return _pointsRegret.values().back();
    }
    qDebug () << "return dont have regrets!.";
    return -1;
//    bool * visited = new bool[instance()->numPoints()];
//    unsigned short i, count, found;
//    double min;
//
//    ++big;
//
//    for ( i = 0; i < instance()->numPoints(); ++i ){
//        visited[i] = false;
//    }
//    found = 0;
//    for ( i = 0 ; i < big; ++i ){
//        min = 0.0;
//        for ( count = 0; count < instance()->numPoints(); count++ ) {
//            if ( !visited[count] )
//            {
//                if ( pointRegret(count) > min ) {
//                    min = pointRegret(count);
//                    found = count;
//                }
//            }
//        }
//        visited[found] = true;
//    }
//    delete [] visited;
//    return found;

}

int DensityCluster::greatDensity(){
    if (_pointsDensity.size() > 0){
        return _pointsDensity.values().back();
    }
    qDebug() << "Dont have density.";
    //
    //    bool * visited = new bool[instance()->numPoints()];
    //    unsigned short i, count, found;
    //    double min;
    //
    //    ++big;
    //
    //    for ( i = 0; i < instance()->numPoints(); ++i )
    //    {
    //        visited[i] = false;
    //    }
    //    //     visited[point] = true;
    //
    //    for ( i = 0 ; i < big; ++i )
    //    {
    //        min = 0.0;
    //        for ( count = 0; count < instance()->numPoints(); count++ ) {
    //            if ( !visited[count] )
    //            {
    //                if ( pointDensity(count) > min ) {
    //                    min = pointDensity(count);
    //                    found = count;
    //                }
    //            }
    //        }
    //        visited[found] = true;
    //    }
    //    delete [] visited;
    //    //could be return found initialized. in case of all points have density == 0.0
    return -1;

}
