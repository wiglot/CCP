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

#include "readccp.h"
#include "Instance.h"
#include <QStringList>
#include <QFile>
#include <QDebug>

using namespace CCP;

Instance * readCCP::readSimpleTXT(QString name){
  QString line;
  QStringList list;
  QList<Point*> pointsList;
  Instance * inst = new Instance;
  
  QFile file(name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Can't open file: " + name; 
    return 0;
  }
  QTextStream input(&file);
  if (!input.atEnd()){
    line = input.readLine();
    list = line.split(":", QString::SkipEmptyParts);

    inst->setName(list[1].trimmed());
    
  }
  if (!input.atEnd()){
    line = input.readLine();
    list = line.split(":", QString::SkipEmptyParts);
    inst->setCapacity(list[1].toDouble());
  }
  if (!input.atEnd()){
    line = input.readLine();
    list = line.split(":", QString::SkipEmptyParts);
    inst->setNumCenters(list[1].toUShort());
  }
  while (!input.atEnd()){
    Point * p = new Point;
    line = input.readLine();
    list = line.split(":", QString::SkipEmptyParts);
    p->setDemand(list[3].toDouble());
    p->setPosition(Position(list[1].toDouble(), list[2].toDouble()));
    pointsList.append(p);
  }
  Point ** points = new Point*[pointsList.size()];
  for (unsigned short i = 0; i < pointsList.size() ; ++i){
      points[i] = pointsList[i];
  }
  inst->setPoints(points,pointsList.size());
  
  return inst;
}