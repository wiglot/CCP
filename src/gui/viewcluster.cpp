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
#include <QRectF>
#include <QDebug>


ViewCluster::ViewCluster(QWidget * parent)
    :QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 400, 400);
    setRenderHint(QPainter::Antialiasing);
    setScene(scene);
}
void ViewCluster::setInstance(CCP::Instance *inst){
    double maxX, maxY, minX, minY;
    clearSolution();
    this->scene()->clear();

    if (inst == 0){
        return;
    }
    minY = minX = 1e10;

    for (unsigned short i = 0; i < inst->numPoints(); i++){
        CCP::Point * p = inst->point(i);
        minX = qMin(minX, p->position().x());
        minY = qMin(minY, p->position().y());
        maxX = qMax(maxX, p->position().x());
        maxY = qMax(maxY, p->position().y());

    }
    for (unsigned short i = 0; i < inst->numPoints(); i++){
        CCP::Point * p = inst->point(i);
        scene()->addEllipse(p->position().x() - 2 ,
                            p->position().y() - 2 ,
                            4, 4);
        qDebug() << p->position().x() - minX -2 << p->position().y() - minY -2 ;
    }

    qDebug() << minX-10 << minY-10 << maxX+10 << maxY+10;
    _instance = inst;
    _instanceSize.setCoords(minX-10, minY-10, maxX+10, maxY+10);

    this->scene( )->setSceneRect(_instanceSize);
    this->fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);

}

void ViewCluster::setSolution(CCP::Solution * sol){
    CCP::Point * tmpCenter = 0;
    _sol = sol;
    if (!sol->isValid()){
        setInstance(_instance);
        return;
    }
    scene()->clear();
    qreal ellipseSize = (qMin(_instanceSize.width(), _instanceSize.height())/_instance->numPoints());
    this->fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);

    for (unsigned short i = 0; i < _instance->numCenters(); i++){
        tmpCenter = _sol->centerOfCluster(i);
        scene()->addEllipse(tmpCenter->position().x() - ellipseSize*0.5,
                                        tmpCenter->position().y() - ellipseSize*0.5,
                                        ellipseSize, ellipseSize, QPen(QBrush(Qt::blue), 2));
        for (unsigned short k = 0; k < _sol->cluster(i)->numPoints(); ++k){
            scene()->addEllipse(_sol->cluster(i)->getPoint(k)->position().x() - ellipseSize*0.35 ,
                                            _sol->cluster(i)->getPoint(k)->position().y() -  ellipseSize*0.35 ,
                                            ellipseSize*0.7, ellipseSize*0.7,
                                            QPen(QBrush(Qt::black), 2));
            scene()->addLine(tmpCenter->position().x() ,
                             tmpCenter->position().y() ,
                             _sol->cluster(i)->getPoint(k)->position().x() ,
                             _sol->cluster(i)->getPoint(k)->position().y()
                             );
	}
    }
}

void ViewCluster::clearSolution(){
    foreach (QGraphicsItem* item, _solItens){
        scene()->removeItem(item);
    }
}
