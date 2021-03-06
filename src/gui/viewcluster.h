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

#ifndef VIEWCLUSTER_H
#define VIEWCLUSTER_H

#include <QGraphicsView>

#include "Solution.h"
#include "../model/History.h"
class QWheelEvent;

class ViewCluster: public QGraphicsView {
    Q_OBJECT;
    CCP::Solution* _sol;
    CCP::Instance* _instance;
    QRectF _instanceSize;

    QList <QGraphicsItem*> _solItens;
    void clearSolution();
  public:
    ViewCluster(QWidget * parent = 0);

void wheelEvent(QWheelEvent *event);

void mousePressEvent(QMouseEvent *event);
void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void setInstance (CCP::Instance * inst);
    void setSolution(CCP::Solution * sol);
    void viewHistoryStep(CCP::HistoryStep step );
    CCP::Solution* solution() {return _sol;}



  void zoomInc();
  void zoomDec();

  void zoom100();

};

#endif // VIEWCLUSTER_H
