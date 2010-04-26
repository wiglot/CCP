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

#ifndef POSITION_H
#define POSITION_H

#include "model_global.h"

#include <cmath>

/**
 * Namespace
 */
namespace CCP { 
/**
 * Class Position
 */
 class CCPModelLib_EXPORT Position {
/**
 * Public stuff
 */
public:

    /**
     * Constructors
     */
    /**
     * Empty Constructor
     */
    Position ( ) { }
    Position (double x, double y) {
      _x = x;
      _y = y;
    }
    /**
     * Accessor Methods
     */
    /**
     * 
     */
    double x ( ) {
        return _x;
    }
    /**
     * 
     */
    void setX (double value ) {
        _x = value;
    }
    /**
     * 
     */
    double y ( ) {
        return _y;
    }
    /**
     * 
     */
    void setY (double value ) {
        _y = value;
    }
    double distance(const Position p){
      return sqrt((this->_x - p._x)*(this->_x - p._x) + (this->_y - p._y)*(this->_y - p._y));
    }

/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     double _x;
     double _y;
    
};
} 
#endif //POSITION_H

