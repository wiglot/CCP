#include "RunData.h"
#include "ui_RunData.h"
#include <Solution.h>

RunData::RunData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunData)
{
    ui->setupUi(this);
}

RunData::~RunData()
{
    delete ui;
}

void RunData::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RunData::setData(CCP::Solution * sol){
    ui->lineAlgorithm->clear();
    ui->lineValue->clear();
    ui->lineTime->clear();
    ui->lineIterations->clear();

    if (sol->isValid()){
        ui->lineAlgorithm->setText(sol->algorithmName());
        ui->lineValue->setText(QString::number(sol->getValue()));
        ui->lineTime->setText(QString::number(sol->timeTaken()));
        ui->lineIterations->setText(QString::number(sol->iterations()));
    }

}
