/*
Wagner de Melo Reck (wagner.reck@gmail.com)

CCP

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

#include "HMeansCluster.h"
#include "densitycluster.h"
#include <QTime>
#include <QDebug>


HMeansCluster::HMeansCluster(CCP::Instance* inst): AlgorithmStruct(inst)
{

}


HMeansCluster::~HMeansCluster()
{

}


CCP::Cluster** HMeansCluster::buildClusters()//CCP::HMeans)
{
    selectRandonInitialCenters();
    return HMeansMethod();
}

CCP::Cluster** HMeansCluster::HMeansMethod()
{
    bool changed = true;

    while (changed){

        if (incIter() > 1000){
            return _centers;
        }
        //Remove all points
        unAssignAllConsumers();

        //re-assign points to nearst center...
        assignToNearest();

        //Try find bests centers
        changed = findBestCenters();
    }

    return _centers;

}


void HMeansCluster::selectRandonInitialCenters(){
    qsrand(QTime::currentTime().msec());
    int i;

    for (i = 0; i < instance()->numCenters(); ++i){
        int gen;
        do{
            gen = qrand() % instance()->numPoints();
        }while (isAssigned(gen));
        assign(gen,i,CCP::Center);
    }
}

void HMeansCluster::selectDensityInitialCenters(){
    int i;
    DensityCluster density(instance());

    density.calculateDensity();

    for (i = 0; i < instance()->numCenters(); ++i){
        int gen;
        do{
            gen = density.greatDensity();
        }while (isAssigned(gen));

        assign(gen,i,CCP::Center);

    }
}
