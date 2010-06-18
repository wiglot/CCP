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

#include "InstanceInfo.h"
#include <QObject>


InstanceInfo::InstanceInfo(CCP::Instance* inst):_inst(inst)
{
    _demandMean = 0.0;
    _demandMax = 0.0;
    _demandMin = 1000000.0;
    _minDistance= 1000000.0;
    _maxDistance = 0;
    _numCentroids = 0;

}

void InstanceInfo::calculateValues() {
    QScopedArrayPointer<bool> visited(new bool[_inst->numPoints()]);
    CCP::Position centroid;
    QList<int> neibour;
    _numCentroids = 0;
    double acumDistance = 0.0;
    double centroidDemand;
    double centroidMin, centroidMax, centroidAcum;
    int visitedPoints = 0;
    for (int i =0; i < _inst->numPoints(); ++i) {
        visited[i] = false;
    }

    while (visitedPoints < _inst->numPoints()) {
        centroid = calculateMassCenter(visited.data());

        neibour = findNeibour(centroid, visited.data());

        _numCentroids++;
        centroidMax =  centroidAcum = centroidDemand = 0.0;
        centroidMin = 10000000.0;
        foreach(int point, neibour) {
            double dist = centroid.distance(_inst->point(point)->position());
            _minDistance = qMin(_minDistance, dist);
            _maxDistance = qMax(_maxDistance, dist);
            acumDistance += dist;
            centroidMin = qMin(centroidMin, dist);
            centroidMax = qMax(centroidMax, dist);
            centroidAcum += dist;
            centroidDemand += _inst->point(point)->demand();
            visited[point] = true;
            ++visitedPoints;
        }
        //centroidAcum / neibour.count();
        _centroidsMeanPoints += neibour.count();
        _centroidsMeanDemand += centroidDemand;
    }
    _centroidsMeanDemand /= _numCentroids;
    _centroidsMeanDemand /=_inst->capacity();
    _centroidsMeanPoints /= _numCentroids;
    _distanceMean = acumDistance / _inst->numPoints();
}

QList< int > InstanceInfo::findNeibour(CCP::Position arg1, bool* visited)
{
    QMultiMap<double, int> map;
    double acum = 0.0;
    QList<int> ret;

    for (int i =0; i < _inst->numPoints(); ++i) {
        if (!visited[i]) {
            map.insert(arg1.distance(_inst->point(i)->position()), i);
        }
    }
    int k = 0;

    while ( k < map.count() &&  acum + _inst->point(map.values().value(k))->demand() < _inst->capacity()) {
        acum += _inst->point(map.values().value(k))->demand();
        ret.append(map.values().at(k));
        k++;
    }
    return ret;
}


CCP::Position InstanceInfo::calculateMassCenter(bool* arg1)
{
    double tmpX = 0.0;
    double tmpY = 0.0;
    double dmd = 0.0;

    for (int i =0; i < _inst->numPoints(); ++i) {
        if (!arg1[i]) {
            CCP::Point * p = _inst->point(i);
            tmpX += p->position().x() * p->demand();
            tmpY += p->position().y() * p->demand();
            dmd += p->demand();
        }
    }
    return CCP::Position(tmpX/dmd, tmpY/dmd);
}


void InstanceInfo::calculate() {
    if (_inst == 0) {
        return;
    }

    _centroidsMeanPoints = 0.0;
    _centroidsMeanDemand = 0.0;

    calculateDemandMean();
    calculateValues();
    double maxDistance = 0;
    for (int i = 0; i < _inst->numPoints(); ++i){
      maxDistance =  qMax(maxDistance, _inst->distance(i,_inst->distancesMatrixes()->near(i, _inst->numPoints()-1)));
    }
    _maxDistance /=maxDistance;
    _minDistance /=maxDistance;
    _distanceMean /= maxDistance;
}

void InstanceInfo::calculateDemandMean()
{
    double acum = 0.0;
    for (int i = 0; i < _inst->numPoints(); i++) {
        acum += _inst->point(i)->demand();
        _demandMin = qMin(_inst->point(i)->demand(), _demandMin);
        _demandMax = qMax(_inst->point(i)->demand(), _demandMax);
    }
    _demandMean = acum/_inst->numPoints();
}


double InstanceInfo::demandMean()
{
    if (_demandMean == 0.0) {
        calculate();
    }
    return _demandMean;
}


double InstanceInfo::tight()
{
    if (_inst != 0)
        return _inst->tight();
    return 0.0;
}


QString InstanceInfo::report()
{
    return QObject::tr("Tight %8 Demand Mean %1, Min Demand %2, Max Demand %3. MinDistance %4, MaxDistance %5,"
                       "Distance Mean %6 Num. Of Centroids %7. Mean num points by Centroid %9, Mean used demand Centroid %10, ")
                                                                              .arg(_demandMean)
                                                                              .arg(_demandMin)
                                                                              .arg(_demandMax)
                                                                              .arg(_minDistance)
                                                                              .arg(_maxDistance)
                                                                              .arg(_distanceMean)
                                                                              .arg(_numCentroids)
                                                                              .arg(tight())
                                                                              .arg(_centroidsMeanPoints)
                                                                              .arg(_centroidsMeanDemand);
}
