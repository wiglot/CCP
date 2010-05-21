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

#ifndef CCPHISTORY_H
#define CCPHISTORY_H

#include <QObject>
#include "../src/model/Instance.h"

class CCPHistory:public QObject {
    Q_OBJECT
        CCP::Instance* instance;
    private slots:
       void initTestCase();
       void checkHistory();
       void changeIteraction();
       void firstStep();
       void lastStep();
       void changeSteps();
       void tryForwardAtEnd();
       void tryBackwardAtBegin();

};

#endif // CCPHISTORY_H
