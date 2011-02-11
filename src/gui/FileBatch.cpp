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

#include "FileBatch.h"
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <qfiledialog.h>
#include "MainWindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QLineEdit>
#include <Instance.h>
#include <QLabel>
#include <InstanceInfo.h>
#include <qscriptengine.h>
#include <SolutionRunner.h>
#include <qtimer.h>


FileBatch::FileBatch(QWidget* parent, Qt::WindowFlags f): QDialog(parent, f)
{

  QGridLayout * lay = new QGridLayout(this);
  _filesList = new QListWidget(this);
  lay->addWidget(_filesList, 0,0,0,1);

  _addFiles = new QPushButton(tr("Add Files"), this);
  lay->addWidget(_addFiles, 0,1);
  _removeFile = new QPushButton(tr("remove File"), this);
  lay->addWidget(_removeFile,1,1);
  _process = new QPushButton(tr("Process"), this);
  lay->addWidget(_process,3,1);
  _close = new QPushButton(tr("Close"), this);
  lay->addWidget(_close,4,1);

  ///////////
  _farthest = new QCheckBox(tr("Fartehst"), this);
  _farthest->setCheckState(Qt::Checked);
  lay->addWidget(_farthest,0,2);
  _density = new QCheckBox(tr("Density"), this);
  _density->setCheckState(Qt::Checked);
  lay->addWidget(_density,1,2);
  _hmeans = new QCheckBox(tr("Hmeans"), this);
  _hmeans->setCheckState(Qt::Checked);
  lay->addWidget(_hmeans,2,2);
  _jmeans = new QCheckBox(tr("Jmeans"), this);
  _jmeans->setCheckState(Qt::Checked);
  lay->addWidget(_jmeans,3,2);

  _jmeansDensity = new QCheckBox(tr("Jmeans Density"), this);
  _jmeansDensity->setCheckState(Qt::Unchecked);
  lay->addWidget(_jmeansDensity,1,4);
  _hmeansDensity = new QCheckBox(tr("Hmeans Density"), this);
  _hmeansDensity->setCheckState(Qt::Checked);
  lay->addWidget(_hmeansDensity,2,4);
  _densityRandom = new QCheckBox(tr("Density Randon"), this);
  _densityRandom->setCheckState(Qt::Checked);
  lay->addWidget(_densityRandom,3,4);
QLabel lab("Repeat times:", this);
  lay->addWidget(&lab, 0,5);
  _times = new QLineEdit(tr("Repeat times"), this);
  _times->setToolTip(tr("You can use keywords like \'clusters\' and \'points\'"));
  lay->addWidget(_times,1,5);

  _changeTight = new QCheckBox(tr("Change Tight"), this);
  _changeTight->setCheckState(Qt::Unchecked);
  lay->addWidget(_changeTight,2,5);

  _emitReport = new QCheckBox(tr("Process info from instances"), this);
  _emitReport->setCheckState(Qt::Unchecked);
  lay->addWidget(_emitReport,3,5);
  _applyImprovement = new QCheckBox(tr("Apply improvments"), this);
  _applyImprovement->setChecked(false);
  lay->addWidget(_applyImprovement, 4,5);


  this->setLayout(lay);

  connect (_process, SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect (_close, SIGNAL(clicked(bool)), this, SLOT(close()));
  connect (_addFiles, SIGNAL(clicked(bool)), this, SLOT(searchFile()));
  connect (_removeFile, SIGNAL(clicked(bool)), this, SLOT(removeFile()));

  MainWindow * main = qobject_cast< MainWindow* >(parent);
  if (main){
      connect(this, SIGNAL(openFile(QString)), main, SLOT(openFile(QString)));
      connect(this, SIGNAL(process(CCP::HeuristicType, bool, bool)), main, SLOT(runAlgorithm(CCP::HeuristicType,bool, bool)));
      connect(this, SIGNAL(saveResults(QString&)), main, SLOT(saveResults(QString&)));
  }
}

void FileBatch::accept()
{
  bool ok;
  int times = _times->text().toInt(&ok);
  MainWindow * main = qobject_cast<MainWindow*>(parent());
  if (!ok)
    times = 1;

  bool improve = _applyImprovement->isChecked();

  int tights = 3;
  if (!_changeTight->isChecked()){
      tights = 1;
  }
  for(int i = 0; i < _filesList->count(); ++i){
    QString filename = _filesList->item(i)->text();
    qDebug() << "processing: " << filename;
    double adj = 1.0;
    emit openFile(filename);


    for (int j = 0; j < tights; ++j){
      if (_changeTight->isChecked()){
        adj += 0.1;
        main->instance()->setTight(adj);
      }
      if (_emitReport->isChecked()){
        InstanceInfo info(main->instance());
        QFile f("info.txt");
        if (!f.open(QIODevice::Append)){
          qDebug() << "Cannot open file info.txt to write.";
        }else{
          QTextStream out(&f);
          info.calculate();
          out << info.report() << "\n";
        }
      }
      QString str = _times->text().replace(QRegExp("clusters"), QString::number(main->instance()->numCenters()));
      str = str.replace(QRegExp("points"), QString::number(main->instance()->numPoints()));
      QScriptEngine eng;
      QScriptValue value = eng.evaluate(str).toInt32();
      if (!eng.hasUncaughtException())
          times = value.toNumber();

      if (_farthest->isChecked()){
        emit process(CCP::Farthest, improve, false);
      }
      if (_density->isChecked()){
        emit process(CCP::Density, improve, false);
      }
      if (_hmeans->isChecked()){
        for (int i = 0; i < times; ++i)
            emit process(CCP::HMeans, improve, false);
      }
      if (_jmeans->isChecked()){
        for (int i = 0; i < times; ++i)
            emit process(CCP::JMeans, improve, false);
      }
      if (_densityRandom->isChecked()){
        for (int i = 0; i < times; ++i){
            emit process(CCP::RandonDensity, improve, false);
           main->improveSolution(CCP::HillClimbShiftWithOveload);
//            while (SolutionRunner::New()->isRunning())
//              usleep(100);
        }
      }
      if (_hmeansDensity->isChecked()){
          for (int i = 0; i < times; ++i)
                emit process(CCP::DensityHMeans, improve, false);
      }
      if (_jmeansDensity->isChecked()){
          for (int i = 0; i < times; ++i)
              emit process(CCP::DensityJMeans, improve, false);
      }
    }
    emit saveResults(filename.append(".out"));
  }
  QDialog::accept();
}

void FileBatch::searchFile()
{
  QStringList files = QFileDialog::getOpenFileNames();
  _filesList->addItems(files);
}

void FileBatch::removeFile(){
  _filesList->removeItemWidget(_filesList->currentItem());
}
