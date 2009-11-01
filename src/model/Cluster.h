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

#ifndef CLUSTER_H
#define CLUSTER_H
#include <qtextstream.h>

namespace CCP{
  class Point;
  class Solution;


class Cluster {
private:
      Point * center;
      QList<Point *> points;
      Solution* solution;
      
  public:
    Cluster(Solution * inst);
    ~Cluster();
    void addPoint(Point * p);
    void removePoint(Point * p);
    
    double actualDemand();
    double remainCapacity();
    
    inline void setCenter(Point * center){
//       if (this->center != 0){
// 	 removePoint(center);
//       }
      this->center = center;
//       addPoint(center);
    }
    
    inline Point * getCenter(){
	return this->center;
    }
    Point * getPoint(unsigned short index);
    
    double totalDistance();
    short unsigned int numPoints();
    
};
}
#endif // CLUSTER_H
