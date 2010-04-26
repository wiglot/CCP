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

#ifndef HMEANS_H
#define HMEANS_H

#include "algorithmstruct.h"

// class CCP::Cluster;

class HMeansCluster : public AlgorithmStruct
{
  public:
    HMeansCluster(CCP::Instance* inst);
    ~HMeansCluster();
    CCP::Cluster** buildClusters();
    void selectRandonInitialCenters();
    void selectDensityInitialCenters();
    
};

#endif // HMEANS_H
