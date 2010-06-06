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

  _times = new QLineEdit(tr("Repeat times"), this);
  lay->addWidget(_times,0,4);

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
  if (!ok){
    times = 1;
  }
  for(int i = 0; i < _filesList->count(); ++i){
    QString filename = _filesList->item(i)->text();
    qDebug() << "processing: " << filename;
    emit openFile(filename);
    if (_farthest->isChecked()){
      emit process(CCP::Farthest, true, false);
    }
    if (_density->isChecked()){
      emit process(CCP::Density, true, false);
    }
    if (_hmeans->isChecked()){
      for (int i = 0; i < times; ++i)
          emit process(CCP::HMeans, true, false);
    }
    if (_jmeans->isChecked()){
      for (int i = 0; i < times; ++i)
          emit process(CCP::JMeans, true, false);
    }
    if (_densityRandom->isChecked()){
      for (int i = 0; i < times; ++i)
          emit process(CCP::RandonDensity, true, false);
    }
    if (_hmeansDensity->isChecked()){
         for (int i = 0; i < times; ++i)
              emit process(CCP::DensityHMeans, true, false);
    }
    if (_jmeansDensity->isChecked()){
        for (int i = 0; i < times; ++i)
            emit process(CCP::DensityJMeans, true, false);
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
