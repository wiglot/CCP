#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "viewcluster.h"
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QDockWidget>
#include <QTextEdit>
#include <QProgressDialog>
#include <QTreeView>
#include <Instance.h>
#include <Solution.h>
#include <SolutionRunner.h>
#include "SolutionPool.h"
#include <readccp.h>
#include "RunData.h"
#include "RunBatch.h"
#include <SolutionImprovement.h>
#include "HistoryChanger.h"
#include "FileBatch.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupAction();
    setCentralWidget(new ViewCluster(this));
    _solution = 0;
    _instance = 0;

    RunData * run = new RunData(this);
    QDockWidget *dockWidget = new QDockWidget(tr("Results"), this);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    dockWidget->setWidget(run);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);


    HistoryChanger * history = new HistoryChanger(this);
    history->setView((ViewCluster*) this->centralWidget());
    QDockWidget *historykWidget = new QDockWidget(tr("History Changer"), this);
    historykWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    historykWidget->setWidget(history);
    addDockWidget(Qt::RightDockWidgetArea, historykWidget);


    SolutionTreeModel * pool = new SolutionTreeModel(this);
    QTreeView *table = new QTreeView(this);
    table->setModel(pool);

    QDockWidget *TabledockWidget = new QDockWidget(tr("Results' table"), this);
    TabledockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    TabledockWidget->setWidget(table);
    addDockWidget(Qt::BottomDockWidgetArea, TabledockWidget);

    _text = new QTextEdit(this);
    _text->setReadOnly(true);
    QDockWidget *TXTdockWidget = new QDockWidget(tr("Text results"), this);
    TXTdockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    TXTdockWidget->setWidget(_text);
    addDockWidget(Qt::BottomDockWidgetArea, TXTdockWidget);

    RunBatch * runWidget = new RunBatch(this);
    addDockWidget(Qt::RightDockWidgetArea, runWidget);

    connect (this, SIGNAL(newInstance(CCP::Instance*)), centralWidget(), SLOT(setInstance(CCP::Instance*)));
    connect (this, SIGNAL(closing()), pool, SLOT(clear()));

    connect(table, SIGNAL(activated(QModelIndex)), pool, SLOT(selectedItem(QModelIndex)));
    connect (pool, SIGNAL(selectedSolution(CCP::Solution*)), this, SLOT(showSolution(CCP::Solution*)));

    connect (this, SIGNAL(newSolution(CCP::Solution*)), centralWidget(), SLOT(setSolution(CCP::Solution*)));
    connect (SolutionRunner::New(), SIGNAL(finished(CCP::Solution*)), pool, SLOT(newSolution(CCP::Solution*)));

    connect (SolutionRunner::New(), SIGNAL(finished(CCP::Solution*)), this, SLOT(finishedAlgorithm(CCP::Solution*)));

    connect (runWidget, SIGNAL(runAlgorithm(CCP::HeuristicType,bool)), this, SLOT(runAlgorithm(CCP::HeuristicType, bool)));

    connect (this, SIGNAL(newSolution(CCP::Solution*)), run, SLOT(setData(CCP::Solution*)));
    connect (this, SIGNAL(textResult(QString)), _text, SLOT(insertPlainText(QString)));
    connect (this, SIGNAL(newInstance(CCP::Instance*)), _text, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::setupAction() {
    QMenu * menu = menuBar()->addMenu(tr("File"));
    QAction * act = menu->addAction("Open",this,SLOT(openFile()));
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    act = menu->addAction(tr("Batch Process"),this,SLOT(batchDialog()));
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    act = menu->addAction("Quit",this,SLOT(close()));
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    menu = menuBar()->addMenu(tr("Algorithms"));
    act = menu->addAction("Farthest",this,SLOT(runAlgorithm()));
    act->setData(CCP::Farthest);
    act->setShortcut(QKeySequence(Qt::Key_F));
    act = menu->addAction("Density",this,SLOT(runAlgorithm()));
    act->setData(CCP::Density);
    act->setShortcut(QKeySequence(Qt::Key_D));
    act = menu->addAction("JMeans",this,SLOT(runAlgorithm()));
    act->setData(CCP::JMeans);
    act->setShortcut(QKeySequence(Qt::Key_J));
    act = menu->addAction("HMeans",this,SLOT(runAlgorithm()));
    act->setData(CCP::HMeans);
    act->setShortcut(QKeySequence(Qt::Key_H));
    menu->addSeparator();
    act = menu->addAction("HMeans With Density",this,SLOT(runAlgorithm()));
    act->setData(CCP::DensityHMeans);
    act->setShortcut(QKeySequence(Qt::Key_N));
    act = menu->addAction("Density With Random",this,SLOT(runAlgorithm()));
    act->setData(CCP::RandonDensity);
    act->setShortcut(QKeySequence(Qt::Key_R));
    act = menu->addAction("JMeans With Density",this,SLOT(runAlgorithm()));
    act->setData(CCP::DensityJMeans);
    act->setShortcut(QKeySequence(Qt::Key_M));


    menu = menuBar()->addMenu(tr("Improvments"));
    act = menu->addAction("Hill Climb whit Shift",this, SLOT(improveSolution()));
    act->setData(CCP::HillClimbShift);
    act = menu->addAction("Hill Climb whit Interchange",this, SLOT(improveSolution()));
    act->setData(CCP::HillClimbInterchange);
    act = menu->addAction("SA whit Shift",this, SLOT(improveSolution()));
    act->setData(CCP::SimulatedAnnelingShift);
    act = menu->addAction("SA whit Interchange",this, SLOT(improveSolution()));
    act->setData(CCP::SimulatedAnnelingInterchange);


}

void MainWindow::saveResults(QString& filename)
{
    QFile fp(filename);
    if (!fp.open(QIODevice::Append|QIODevice::Text)) {
        qDebug() << "Error writting file! " << filename;
        return;
    }
    QTextStream str(&fp);
    str << "\nInstance "<<_instance->name() << " " << QDateTime::currentDateTime().toString() ;
    str << _text->document()->toPlainText();
}


void MainWindow::closeInstance() {
    _solution = 0;

    if (_instance) {
        emit closing();
        delete _instance;
        _instance = 0;
    }
}

void MainWindow::batchDialog()
{
    FileBatch f(this);
    f.exec();
}


void MainWindow::openFile(QString filename) {
    CCP::Instance * inst = 0;

    if (filename.isEmpty()) {
        QFileDialog f(this);
        f.setFilters(QStringList() << "Dat type (*.dat)"<<"Text files (*.txt)");
        if (f.exec()) {
            if (f.selectedFiles().count() == 0) {
                return;
            }
            closeInstance();

            filename = f.selectedFiles().at(0);
        }else {
            return;
        }
    }
    if (filename.endsWith(".dat")) {
        inst = readCCP::readLorenaEuclidian(filename);
    } else if (filename.endsWith(".txt")) {
        inst = readCCP::readSimpleTXT(filename);
    }
    if (inst != 0){
      new CCP::Distance(inst);
      emit newInstance(inst);
      _instance = inst;
    }else{
        _text->insertPlainText(QString("Cannot open the file %1").arg(filename));
    }
}

void MainWindow::runAlgorithm( CCP::HeuristicType inType, bool improve, bool useThread) {
    CCP::HeuristicType type;
    QAction * act = qobject_cast<QAction*>(sender());

    if (act) {

        switch (act->data().toInt()) {
        case CCP::HMeans:
            type = CCP::HMeans;
            break;
        case CCP::JMeans:
            type = CCP::JMeans;
            break;

        case CCP::Farthest:
            type = CCP::Farthest;
            break;

        case CCP::Density:
            type = CCP::Density;
            break;

        case CCP::DensityHMeans:
            type = CCP::DensityHMeans;
            break;

        case CCP::RandonDensity:
            type = CCP::RandonDensity;
            break;
        case CCP::DensityJMeans:
            type = CCP::DensityJMeans;
            break;
        }
    } else {
        type = inType;
    }
    SolutionRunner::queue(_instance, type, improve, useThread);

}

void MainWindow::improveSolution() {
    if (_solution == 0) {
        return;
    }
    QAction * act = qobject_cast<QAction*>(sender());
    if (act) {
        switch (act->data().toInt()) {
        case CCP::HillClimbShift:
            SolutionRunner::queue(_solution, CCP::HillClimbShift);
            break;
        case CCP::HillClimbInterchange:
            SolutionRunner::queue(_solution, CCP::HillClimbInterchange);
            break;

        case CCP::SimulatedAnnelingInterchange:
            SolutionRunner::queue(_solution, CCP::SimulatedAnnelingInterchange);
            break;

        case CCP::SimulatedAnnelingShift:
            SolutionRunner::queue(_solution, CCP::SimulatedAnnelingShift);
            break;
        }
    }

}

void MainWindow::finishedAlgorithm(CCP::Solution * sol) {
    if (sol == 0) {
        statusBar()->showMessage("Invalid  solution. ", 2000);

    } else {
        _solution = sol;
        QString result = _instance->printData() + ", " + sol->algorithmName() + ", " + QString::number(sol->getValue()) + ", ";
        result += QString::number(sol->timeTaken()) + ", ";
        result += QString::number(sol->iterations()) + ",\n";
        emit textResult(result);

        showSolution(sol);
    }
}

void MainWindow::showSolution(CCP::Solution* sol) {
    if (sol==0)
        return;
    _solution = sol;
    setWindowTitle(sol->algorithmName());
    emit newSolution(sol);
}
