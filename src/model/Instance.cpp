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

#include "Instance.h"
#include "Distance.h"


/**
 * Constructors/Destructors
 */


CCP::Instance::~Instance(){
//     for (count = 0; count < this->_numPoints; ++count)
//       delete _points;
    delete [] _points;
    delete _distance;
}
/**
 * Methods
 */
double CCP::Instance::distance (short unsigned int p1, short unsigned int p2, double factor){
    return this->_distance->distance(p1, p2) * factor;
}

double CCP::Instance::distance (Point * p1, Point * p2, double factor){
    return this->distance(pointIndex(p1), pointIndex(p2), factor);
}


double CCP::Instance::tight(){
  double acum = 0.0;
   for (int i = 0; i < this->_numPoints; ++i){
      acum += _points[i]->demand();
   }
   return acum/this->capacity();
}