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

#include "JMeansWithDensity.h"
#include "densitycluster.h"

CCP::Cluster** JMeansWithDensity::buildClusters()
{
//     selectInitialCenters();
//     jmeansMethod();
    return _centers;
}

void JMeansWithDensity::selectInitialCenters()
{
    int numNeibor = floor( instance()->numPoints() / double(instance()->numCenters())) ;
    DensityCluster d(_myInstance);
    for (int count = 0; count < _myInstance->numCenters(); ++count){
        d.calculateDensity();
        int nextCenter = d.greatDensity();
        QList<int>neibor =  d.findNeiborhood(nextCenter, numNeibor);
        d.assign(nextCenter, count, CCP::Center);
        foreach(int i, neibor){
          d.assign(i, count, CCP::Consumer);
        }
        assign(nextCenter,count, CCP::Center);
    }
}

