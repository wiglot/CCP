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

#include "viewcluster.h"

#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"
#include "Point.h"


ViewCluster::ViewCluster(QWidget * parent)
    :QGraphicsView(parent)
{
  QGraphicsScene * scene = new QGraphicsScene;
  scene->setSceneRect(0, 0, 400, 400);        
  setRenderHint(QPainter::Antialiasing);
  setScene(scene);
}
void ViewCluster::setSolution(CCP::Solution * sol){
    CCP::Point * tmpCenter = 0;
  
    this->_sol = sol; 

    double maxX, maxY, minX, minY;

    maxX = maxY = 0.0;    
    
    scene()->clear();
    CCP::Instance * inst = sol->getInstance();
    minX = inst->point(0)->position().x();
    minY = inst->point(0)->position().y();

    for (unsigned short i = 0; i < inst->numPoints(); i++){
	CCP::Point * p = inst->point(i);
	if (minX > p->position().x())
           minX = p->position().x();
        else{
		if (maxX < p->position().x())
                    maxX = p->position().x();
	}
	if (minY > p->position().y())
           minY = p->position().y();
        else{
		if (maxY < p->position().y())
                    maxY = p->position().y();
	}
    }

    this->scene( )->setSceneRect((int) -50,(int) -50,(int) maxX+50 - minX, (int)maxY+50 - minY);
    this->fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);

    for (unsigned short i = 0; i < inst->numCenters(); i++){
	tmpCenter = sol->centerOfCluster(i);
	scene()->addEllipse(tmpCenter->position().x()-minX-3, tmpCenter->position().y()-minY-3, 6, 6);
	for (unsigned short k = 0; k < sol->cluster(i)->numPoints(); ++k){
	  scene()->addEllipse(sol->cluster(i)->getPoint(k)->position().x()-minX -1 ,
				sol->cluster(i)->getPoint(k)->position().y() - minY -1 ,
                                 2, 2);
	  scene()->addLine(tmpCenter->position().x() -minX,
			   tmpCenter->position().y() -minY,
			    sol->cluster(i)->getPoint(k)->position().x() -minX,
			    sol->cluster(i)->getPoint(k)->position().y() - minY
			    );
	}
    }
}
