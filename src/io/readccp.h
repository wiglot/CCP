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

#ifndef READCCP_H
#define READCCP_H
#include "Instance.h"
#include <qstring.h>

class readCCP {
  public:
    /** @brief Read a file for a instance.
    *The file mus be in the follow format:
    *name: instance 1
    *Capacity: 5
    *numClusters: 3
    *1: 1.0: 2.0: 4
    *2: 1.0: 1.0: 1 
    * Separator is allway ':' and the points follow this order ID : X : Y : Demand. ID can be a string, others shoud be float numbers.
    * @param filename Name of file (with relative path).
    * @return return a Instance poiter or a null pointer (0) if can't open the filename.
    */
    static CCP::Instance * readSimpleTXT(QString filename);
    
};

#endif // READCCP_H
