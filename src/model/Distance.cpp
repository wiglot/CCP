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

#include "Distance.h"
#include "Point.h"
#include "Instance.h"


/**
 * Constructors/Destructors
 */
CCP::Distance::Distance ( CCP::Instance* inst) :
        _instance ( inst ),
	_numPoints ( inst->numPoints() )
{
    
    unsigned short count, count2;
    this->_values = new double*[_numPoints];
    this->_near = new int*[_numPoints];
    for ( count = 0; count < _numPoints; ++count ){
        this->_values[count] = new double[count];
	this->_near[count] = new int[_numPoints];
        for ( count2 = 0; count2 < _numPoints; ++count2 ) {
	    if (count2 < count)
		_values[count][count2] =-1;
	    _near[count][count2] = -1;
        }
    }
    
    _instance->setDistances ( this );
    
}

CCP::Distance::~Distance()
{
    unsigned short count;
    for ( count = 0; count < _numPoints; ++count ) {
        delete [] _values[count];
	delete [] _near[count];
    }
    delete [] _values;
    delete [] _near;


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
    bool * visited; 
    unsigned short i, count, found;
    unsigned short init = 1;
    double min;
    
    if ( nearest == 0 )
	_near[point][0] = point;
    
    if (_near[point][nearest] != -1){
	return _near[point][nearest];
    }
  
    visited = new bool[_numPoints];
    for ( i = 0; i < _numPoints; ++i )
    {
        visited[i] = false;
    }
    
    visited[point] = true;
    
    
    for (i = nearest-1; i > 0; --i){
	if (_near[point][i] != -1){
	    init = i + 1;
	    for (count = i; count > 0; --count){
		visited[  _near[point][count]  ] = true;
	    }
	    break;
	}
    }
    
    
    for ( i = init ; i <= nearest; ++i )
    {
        min = 2000000;
        for ( count = 0; count < _numPoints; count++ ) {
            if ( !visited[count] )
            {
                if ( distance ( point, count ) < min ) {
                    min = distance ( point, count );
                    found = count;
                }
            }
        }
	_near[point][i] = found;
        visited[found] = true;
    }
    
    delete [] visited;
    
    return _near[point][nearest];
}
