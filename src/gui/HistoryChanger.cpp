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
    stepSize = new QSpinBox(this);
    stepSize->setRange(1, 10);
    stepSize->setValue(1);
    stepSize->setSuffix(tr(" Step"));

    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(0);

    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(minus,0,0);
    lay->addWidget(plus,0,1);
    lay->addWidget(stepSize,1,0);
    lay->addWidget(slider,2,0,1,0);

    _view = 0;

    connect (plus, SIGNAL(clicked(bool)), this, SLOT(nextStep()) );
    connect (minus, SIGNAL(clicked(bool)), this, SLOT(backStep()) );
    connect (slider, SIGNAL(valueChanged(int)), this, SLOT( gotToStep(int)));

}


HistoryChanger::~HistoryChanger() {

}


void HistoryChanger::backStep() {
//     ViewCluster * view = qobject_cast<ViewCluster*>(parentWidget());
    if (_view){
        if (_view->solution() != 0){
            CCP::HistoryStep step = _view->solution()->history()->moveSteps(-stepSize->value());
            _view->viewHistoryStep(step);
            slider->setMaximum(_view->solution()->history()->stepsCount());
            slider->setValue(_view->solution()->history()->actualStep());
        }
    }
}


void HistoryChanger::nextStep() {
//     ViewCluster * view = qobject_cast<ViewCluster*>(parentWidget());
    if (_view){
        if (_view->solution() != 0){
            CCP::HistoryStep step = _view->solution()->history()->moveSteps(stepSize->value());
            _view->viewHistoryStep(step);
            slider->setMaximum(_view->solution()->history()->stepsCount());
            slider->setValue(_view->solution()->history()->actualStep());
        }
    }
}


void HistoryChanger::gotToStep ( int stp) {
    if (_view){
        if (_view->solution() != 0){
            CCP::History * hist = _view->solution()->history();
            if (hist == 0){
                return;
            }
            if (stp <= (hist->stepsCount()-1)){
                    _view->viewHistoryStep(hist->moveSteps(stp - hist->actualStep()));
            }
        }
    }
}

// #include "HistoryChanger.moc"