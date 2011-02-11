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

#ifndef FILEBATCH_H
#define FILEBATCH_H

#include <QtGui/QDialog>
#include <model_global.h>
#include <QListWidget>
class QCheckBox;

class FileBatch : public QDialog
{
Q_OBJECT
public:
    FileBatch(QWidget* parent = 0, Qt::WindowFlags f = 0);
  private slots:
    virtual void accept();
    void searchFile();
    void removeFile();

  signals:
    void openFile(QString);

    void saveResults(QString& arg1);
    void process(CCP::HeuristicType, bool, bool) ;
private:
    QListWidget* _filesList;
    QPushButton* _addFiles;
    QPushButton* _removeFile;
    QPushButton* _process;
    QPushButton* _close;
    QCheckBox* _farthest;
    QCheckBox* _density;
    QCheckBox* _hmeans;
    QCheckBox* _jmeans;
    QLineEdit* _times;
    QCheckBox* _jmeansDensity;
    QCheckBox* _hmeansDensity;
    QCheckBox* _densityRandom;

    QCheckBox* _emitReport;    QCheckBox* _changeTight;
    QCheckBox* _applyImprovement;
};

#endif // FILEBATCH_H
