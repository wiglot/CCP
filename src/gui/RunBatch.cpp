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
        emit runAlgorithm(CCP::Farthest);
    }
    num = ui->densityNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::Density);
    }
    num = ui->hmeansNum->text().toInt();
    for (int i = 0; i < num; ++i){
       emit runAlgorithm(CCP::HMeans);
    }
    num = ui->jmeansNum->text().toInt();
    for (int i = 0; i < num; ++i){
        emit runAlgorithm(CCP::JMeans);
    }
}
