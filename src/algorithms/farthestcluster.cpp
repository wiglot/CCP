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

#include "farthestcluster.h"
#include "../model/Instance.h"
#include "Distance.h"
#include "Cluster.h"
#include <QMultiHash>
#include <QDebug>


using namespace CCP;


CCP::Cluster** FarthestCluster::buildClusters(){
    //     this->_centers = new Cluster*[_myInstance->numCenters()];
    //     for (unsigned short count = 0 ; count < _myInstance->numCenters(); ++count){
    // 	this->_centers[count] = new Cluster(_myInstance);
    //     }
    this->selectFirstCenters();
    this->findBasicClusters();
    this->findBestCenters();
    return this->_centers;
}

void FarthestCluster::selectFirstCenters() {
    unsigned short count, center1 = 0, center2=0, numPoints = instance()->numPoints();
    //long distance = 0, max = 0;
    //short unsigned int centerFound;
    double max = 0;
    for ( count = 0; count < numPoints; ++count ) {
        double distance = instance()->distance( count, instance()->distancesMatrixes()->near( count, numPoints - 1 ) );
        if ( distance > max ) {
            max = distance;
            center1 = count;
            center2 = instance()->distancesMatrixes()->near( count, numPoints - 1 );
        }
    }
    if (center1 == center2)
        return;

    assign(center1, 0,CCP::Center);
    assign(center2, 1,CCP::Center);

    int centersInserted = 2;
    QMultiMap <double, int> distances;
    for ( count = 0; count < numPoints; ++count ) {
        if (count != center2 && count != center1)
            distances.insert((instance()->distance(count, center1) * instance()->distance(count, center2)), count);
    }

    //    distances.remove(0);

    while ( instance()->numCenters() > centersInserted ) {
        qDebug() << distances.size();
        int insertedCenter = distances.value(distances.keys().last());

        assign(distances.value(distances.keys().last()), centersInserted++, CCP::Center);
        qDebug() << "Removed: " << distances.remove(distances.keys().last(),insertedCenter);

        QList <double> keys = distances.keys();
        qDebug() << distances.size();

         double minor = 0.0;
         do {
            minor = keys.at(0);
            if (minor == 0){
                distances.remove(minor, distances.value(minor));
		keys = distances.keys();
 
            }
         }while (minor == 0);
        foreach (double key, keys){
            qreal distance = key / minor;
            int p = distances.value(key);
            distance *= instance()->distance(  p, insertedCenter );
            if (distance != key){
                distances.insert(distance, p);

                if (distances.remove(key, p) != 1){
                    qDebug() << key << p;

                }
            }
        }

    }
}

void FarthestCluster::findBasicClusters() {
    unsigned short  count, count2;
    Point * selectedPoint;
    unsigned short clusterToAdd;
    double indicator = 0.0;

    CCP::Cluster * tmpcluster;


    for ( count2 = 0; count2 < instance()->numPoints(); ++count2 ) {
        if ( this->pointType(count2) == CCP::Consumer ) {
            selectedPoint = instance()->point( count2 );
	    indicator = 3000000.0;
	    clusterToAdd = instance()->numPoints();
            for ( count = 0; count < instance()->numCenters(); ++count ) {
                tmpcluster = this->cluster(count);
                if ( tmpcluster->remainCapacity() >= selectedPoint->demand() ) {
		    double tmp = instance()->distance(selectedPoint, tmpcluster->getCenter(),
                                                      selectedPoint->demand());
		    if (tmp <= indicator){
			indicator = tmp;
			clusterToAdd = count;
		    }
                }
            }
	    if (clusterToAdd == instance()->numPoints()){
            qDebug() << "There is no cluster with capacity to suporte a point";
            return;
                //throw QString ("There is no cluster with capacity to suporte a point");
	    }
	    assign(selectedPoint, clusterToAdd);
            // 	    tmpcluster = this->cluster(clusterToAdd);
            // 	    tmpcluster->addPoint(selectedPoint);
        }
    }
}

