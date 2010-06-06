#include "RunBatch.h"
#include "ui_RunBatch.h"
#include <QString>
#include <Solution.h>


RunBatch::RunBatch(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RunBatch)
{
    ui->setupUi(this);
}

RunBatch::~RunBatch()
{
    delete ui;
}

void RunBatch::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RunBatch::run(){
    int num = ui->farthestNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::Farthest, ui->improve->isChecked());
    }
    num = ui->densityNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::Density, ui->improve->isChecked());
    }
    num = ui->hmeansNum->text().toInt();
    for (int i = 0; i < num; ++i){
       emit runAlgorithm(CCP::HMeans, ui->improve->isChecked());
    }
    num = ui->jmeansNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::JMeans, ui->improve->isChecked());
    }
    num = ui->randomDensityNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::RandonDensity, ui->improve->isChecked());
    }
    num = ui->jmeansDensityNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::DensityJMeans, ui->improve->isChecked());
    }
    num = ui->hmeansDensityNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::DensityHMeans, ui->improve->isChecked());
    }
}
