/*
Wagner de Melo Reck (wagner.reck@gmail.com)

CCP

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

#include "HistoryChanger.h"
#include <QGridLayout>
#include "viewcluster.h"
#include <QDebug>


HistoryChanger::HistoryChanger ( QWidget* parent, Qt::WindowFlags f ) : QWidget ( parent, f ) {
    plus = new QPushButton("Next",this);
    minus = new QPushButton("back",this);
    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(minus,0,0);
    lay->addWidget(plus,0,1);

    _view = 0;

    connect (plus, SIGNAL(clicked(bool)), this, SLOT(nextStep()) );
    connect (minus, SIGNAL(clicked(bool)), this, SLOT(backStep()) );

}


HistoryChanger::~HistoryChanger() {

}


void HistoryChanger::backStep() {
//     ViewCluster * view = qobject_cast<ViewCluster*>(parentWidget());
    if (_view){
        if (_view->solution() != 0){
            CCP::HistoryStep step = _view->solution()->history()->stepBackward();
            _view->viewHistoryStep(step);
        }
    }
}


void HistoryChanger::nextStep() {
//     ViewCluster * view = qobject_cast<ViewCluster*>(parentWidget());
    if (_view){
        if (_view->solution() != 0){
            CCP::HistoryStep step = _view->solution()->history()->stepFoward();
            _view->viewHistoryStep(step);
        }
    }
}


// #include "HistoryChanger.moc"