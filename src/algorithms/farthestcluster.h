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

#ifndef FARTHESTCLUSTER_H
#define FARTHESTCLUSTER_H

#include "algorithmstruct.h"

class FarthestCluster:public AlgorithmStruct {
  private:
    void selectFirstCenters();
    void findBasicClusters();
    
    /** @brief seek for wich is the best center of clusters.
    */
    void findBestCenters();
  public:
     
    FarthestCluster(CCP::Instance* inst):AlgorithmStruct(inst){ }
    CCP::Cluster** buildClusters();
};

#endif // FARTHESTCLUSTER_H
