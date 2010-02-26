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
#include <QDebug>
#include <QTime>
#include <QApplication>
#include "Instance.h"
#include <readccp.h>
#include "Solution.h"
#include "gui/MainWindow.h"

using namespace CCP;

int main(int argc, char** argv)
{

    QApplication app(argc, argv);


  MainWindow view;
//  view.setSolution(sol);
  view.show();
  
 
  return app.exec();


 
//     Instance * foo;
//     QCoreApplication app(argc, argv);
//     if (argc > 1){
// 	foo = readCCP::readLorenaEuclidian(argv[1]);
//     }else {
// 	foo = readCCP::readSimpleTXT("../instances/instance1.txt");
//     }
//     
//     Solution * sol = new Solution(foo);
//     sol->constructSolution(CCP::Density);
//     for (unsigned short i = 0; i < foo->numCenters(); ++i){
// 	  qDebug() << i+1 << " - " << foo->pointIndex(sol->centerOfCluster(i));
//     }
//     return app.exec();
}
