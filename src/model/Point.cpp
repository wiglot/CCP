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

#include "Point.h"
#include "Position.h"
/**
 * Constructors/Destructors
 */
CCP::Point::Point ( ):_pos(Position(0.0,0.0)), _demand(0.0), m_index(-1){

}
CCP::Point::Point (double x, double y, double demand):_pos(Position( x,y)), _demand(demand), m_index(-1){
  
}

/**
 * Methods
 */

