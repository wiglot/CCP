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

#include "algorithmstruct.h"
#include "Instance.h"

using namespace CCP;


AlgorithmStruct::AlgorithmStruct( Instance* inst ):
  _myInstance(inst)
{
  _assigned = new int[_myInstance->numPoints()];
  for (unsigned short count = 0; count < _myInstance->numPoints(); ++count){
     unAssign(count); 
  }
}


double AlgorithmStruct::distance(unsigned short point, QList <int> list){
    double acum = 0.0;
    foreach(int i, list){
	acum += _myInstance->distance(i, point);
    }
    return acum;
}