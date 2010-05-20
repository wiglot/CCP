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

#ifndef HISTORYCHANGER_H
#define HISTORYCHANGER_H
#include <QWidget>
#include <QPushButton>
#include "viewcluster.h"

class HistoryChanger : public QWidget {
    Q_OBJECT
        QPushButton * plus;
        QPushButton * minus;
        ViewCluster * _view;

    public:

        HistoryChanger ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        virtual ~HistoryChanger();

        void setView(ViewCluster * view){_view = view;}

    private slots:
        void nextStep();
        void backStep();

};

#endif // HISTORYCHANGER_H
