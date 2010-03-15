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

#ifndef CLUSTER_H
#define CLUSTER_H
#include <qtextstream.h>
#include <QList>

namespace CCP{
  class Point;
  class Instance;


class InterchangeResult{
  private:
      bool _valid;
      double _change;
      Point* _origP,* _destP;
      class Cluster* _origC,* _destC;

  public:
      InterchangeResult(Point * origPoint, Cluster * origCluster,
                        Point * destPoint, Cluster * destCluster)
      {
          _valid = false;
          _change = 0.0;
          _origP = origPoint;
          _destP = destPoint;
          _destC = destCluster;
          _origC = origCluster;

      }
      ~InterchangeResult(){ }
      inline const bool isValid(){ return _valid;}
      inline double changeInValue(){return _change;}

      void valid(const bool v = true){ _valid = v;}
      void valueChange(double c){_change = c;}
      bool undo();
  };


class Cluster {
private:
      Point * center;
      QList<Point *> points;
      Instance* _instance;
      
  public:
    Cluster(Instance * inst);
    ~Cluster();
    void addPoint(Point * p);
    void removePoint(Point * p);
    
    double actualDemand();
    double remainCapacity();
    
    void setCenter(Point * center);
    
    inline Point * getCenter(){
	return this->center;
    }
    Point * getPoint(unsigned short index);
    Point * takePoint( unsigned short  arg1 );
    double totalDistance();
    short unsigned int numPoints();

    const Cluster operator=(const Cluster &other);
    
    /** @brief Interchage points between Clusters.
    *   To make the interchange, is checked if dest support the origPoint.
    *   At end return if interchange change was done or not.
    *   \param origPoint Point to be moved to \Cluster dest.
    *   \param dest Other cluster to receive origPoint.
    *   \return total change in values of distances.
    */
    InterchangeResult shift(Point* origPoint, Cluster* dest);

    /** @brief Interchage points between Clusters.
    *   To make the interchange, is checked if both suport news points after remove originPoint an retPoint.
    *   At end return changes at distances values.
    *   \param origPoint Point to be moved to \Cluster dest.
    *   \param retPoint Point to be inserted in this cluster.
    *   \param dest Other cluster to receive origPoint.
    *   \return total change in values of distances.
    */
    InterchangeResult shift(Point* origPoint, Point* retPoint,Cluster* dest);
    
};
}
#endif // CLUSTER_H
