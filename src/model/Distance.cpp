#include "Distance.h"
#include "Point.h"
#include "Instance.h"


/**
 * Constructors/Destructors
 */
CCP::Distance::Distance ( Instance * inst ) :
    _numPoints ( inst->numPoints() ),
    _instance ( inst )
{
  _instance->setDistances ( this );
  unsigned short count, count2;
  this->_values = new double*[_numPoints];

  for ( count = 0; count < _numPoints; ++count )
    {
      this->_values[count] = new double[count];
      for ( count2 = 0; count2 < count; ++count2 )
        {
          _values[count][count2] = -1;

        }
    }
}

CCP::Distance::~Distance()
{
  unsigned short count;
  for ( count = 0; count < _numPoints; ++count ) {
      delete _values[count];
    }
  delete [] _values;


}

double CCP::Distance::distanceBetween ( unsigned short int point1, unsigned short int point2 )
{
  CCP::Point * p1 = _instance->point ( point1 );
  CCP::Point * p2 = _instance->point ( point2 );

  if ( p1 == 0 || p2 == 0 )
    {
      return -1;
    }
  else
    {
      return p1->position().distance ( p2->position() );
    }
}


short unsigned int CCP::Distance::near ( unsigned short point, unsigned short nearest )
{
  bool * visited = new bool[_numPoints];
  unsigned short i, count, found;
  double foundedDistance = 0.0;
  double min;

  if ( nearest == 0 )
    return point;

  for ( i = 0; i < _numPoints; ++i )
    {
      visited[i] = false;
    }
  visited[point] = true;
  for ( i = 0 ; i < nearest; ++i )
    {
      min = 2000000;
      for ( count = 0; count < _numPoints; count++ )
        {
          if ( !visited[count] )
            {
              if ( distance ( point, count ) < min ){
                min = distance ( point, count );
		found = count;
	      }
            }
        }
      visited[found] = true;
    }
  return found;
}
