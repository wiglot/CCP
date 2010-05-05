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

#include "JMeansCluster.h"
#include "densitycluster.h"
#include <QList>
#include <QTime>

using namespace CCP;

JMeansCluster::JMeansCluster(Instance* inst): AlgorithmStruct(inst)
{

}


JMeansCluster::~JMeansCluster()
{

}


Cluster** JMeansCluster::buildClusters()
{
    qreal fOpt = 1000000.0;
    qreal fTmp;
    int delC; //Cluster to delete
    int newC; //point to become center.
    QScopedPointer<double>means (new double[_myInstance->numCenters()]);
    QList <int> unoccupied;
//    QList <double> means;

    selectRandonInitialCenters();

    assignToNearest();
    while (incIter() < 1000){
        fTmp = 0.0;
        for (int count = 0; count < _myInstance->numCenters(); ++count){
            fTmp += _centers[count]->totalDistance();
        }
        if (fOpt <= fTmp )
            break;
        else{
            fOpt = fTmp;
        }

        findMeans(means.data());
        unoccupied = findUnoccupied(means.data());

        qreal fIni = fOpt;
        delC = -1;
        newC = -1;
        foreach (int unocc, unoccupied){
            for (int c = 0; c < _myInstance->numCenters(); ++c){
                Point * oldCenter = _centers[c]->getCenter();
                assign(unocc, c, Center);
                assignToNearest();
                //Verify min Value
                fTmp = 0.0;
                for (int count = 0; count < _myInstance->numCenters(); ++count){
                    fTmp += _centers[count]->totalDistance();
                }
                if (fIni > fTmp){
                    fIni = fTmp;
                    delC = c;
                    newC = unocc;

                }
                foreach (int assig, unoccupied){
                    unAssign(assig);
                }
                assign(oldCenter, c, Center);
            }

        }
        if (delC != -1 && newC != -1){
            assign(newC, delC, Center);
        }
        assignToNearest();
    }
    return _centers;
}

void JMeansCluster::findMeans(double * vect){
    int c;
//    QList<double> ret;
    double v = 0.0;
    for (c = 0; c < _myInstance->numCenters(); ++c){
        Cluster * cluster= _centers[c];
        v = cluster->totalDistance()/cluster->numPoints();
        vect[c] = v;
    }
}

QList <int> JMeansCluster::findUnoccupied(double *tolerances){
    QList <int> ret;
    int count;

    for (count = 0; count < _myInstance->numPoints(); ++count){
        //Point* p = _myInstance->point(count);
        int alTo = assignedTo(count);
        if (alTo == -1){
            ret.append(count);
        }else{
            if (_myInstance->distance(count,_centers[alTo]->getCenter()->index())
                 >  tolerances[alTo]){
                ret.append(count);
                unAssign(count);
            }
        }
    }
    return ret;
}

void JMeansCluster::selectRandonInitialCenters(){
    qsrand(QTime::currentTime().msec());
    int i;

    for (i = 0; i < instance()->numCenters(); ++i){
        int gen;
        do{
            gen = qrand() % instance()->numPoints();
        }while (isAssigned(gen));
        assign(gen,i,CCP::Center);
    }
//    int i;
//    DensityCluster density(instance());
//
//    density.calculateDensity();
//
//    for (i = 0; i < instance()->numCenters(); ++i){
//        int gen;
//        do{
//            gen = density.greatDensity();
//        }while (isAssigned(gen));
//        assign(gen,i,CCP::Center);
//
//    }
}
