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

#ifndef POINT_H
#define POINT_H

#include "model_global.h"

#include <string>
#include "Position.h"


/**
 * Namespace
 */
namespace CCP { 

    class Instance;


/**
 * Class Point
 * 
 */
class CCPModelLib_EXPORT Point {
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
    Point ( Instance * inst);
    Point ( Instance * inst, double x, double y, double demand);
    Point (Instance * inst, Position pos, double demand):_inst(inst), _pos(pos), _demand(demand), m_index(-1){ }
    /**
     * Accessor Methods
     */
    CCP::Position position ( ) {
        return _pos;
    }
    /**
     * 
     */
    void setPosition (CCP::Position value ) {
        _pos = value;
    }
    /**
    *
    */
    void setDemand(double value) {
	_demand = value;
    }
    
    double demand(){
	return _demand;
    }
    
    void setIndex(int new_index){
	m_index = new_index;
    }
    
    int index();
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
     Instance * _inst;
     CCP::Position _pos;
     double _demand;
     int m_index;
};
} 
#endif //POINT_H

