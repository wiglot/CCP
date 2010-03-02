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
#include <Instance.h>
#include <Solution.h>
#include <SolutionRunner.h>
#include <readccp.h>
#include "RunData.h"
#include "RunBatch.h"

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

    QTextEdit *text = new QTextEdit(this);
    text->setReadOnly(true);
    QDockWidget *TXTdockWidget = new QDockWidget(tr("Text results"), this);
    TXTdockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
    TXTdockWidget->setWidget(text);
    addDockWidget(Qt::BottomDockWidgetArea, TXTdockWidget);

    RunBatch * runWidget = new RunBatch(this);
    addDockWidget(Qt::RightDockWidgetArea, runWidget);

    connect (this, SIGNAL(newInstance(CCP::Instance*)), centralWidget(), SLOT(setInstance(CCP::Instance*)));
    connect (this, SIGNAL(newSolution(CCP::Solution*)), centralWidget(), SLOT(setSolution(CCP::Solution*)));

    connect (SolutionRunner::New(), SIGNAL(finished(CCP::Solution*)), this, SLOT(finishedAlgorithm(CCP::Solution*)));

    connect (runWidget, SIGNAL(runAlgorithm(CCP::HeuristicType)), this, SLOT(runAlgorithm(CCP::HeuristicType)));

    connect (this, SIGNAL(newSolution(CCP::Solution*)), run, SLOT(setData(CCP::Solution*)));
    connect (this, SIGNAL(textResult(QString)), text, SLOT(insertPlainText(QString)));
    connect (this, SIGNAL(newInstance(CCP::Instance*)), text, SLOT(clear()));
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

void MainWindow::setupAction(){
    QMenu * menu = menuBar()->addMenu(tr("File"));
    QAction * act = menu->addAction("Open",this,SLOT(openFile()));
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    act = menu->addAction("Quit",this,SLOT(close()));
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    menu = menuBar()->addMenu(tr("Algorithms"));
    act = menu->addAction("far",this,SLOT(runAlgorithm()));
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
}

void MainWindow::openFile(){
    QFileDialog f(this);

    f.setFilters(QStringList() << "Dat type (*.dat)"<<"Text files (*.txt)");
    if(f.exec()){
        if (f.selectedFiles().count() == 0){
            return;
        }
        if (_solution){
            delete _solution;
        }
        if (_instance){
            delete _instance;
        }
        QString filename = f.selectedFiles().at(0);
        if (filename.endsWith(".dat")){
            _instance = readCCP::readLorenaEuclidian(filename);

        }else if (filename.endsWith(".txt")){
            _instance = readCCP::readSimpleTXT(filename);

        }
        new CCP::Distance(_instance);

        _solution = 0;
        emit newInstance(_instance);


    }
}

void MainWindow::runAlgorithm( CCP::HeuristicType inType){
    CCP::HeuristicType type;
    QAction * act = qobject_cast<QAction*>(sender());
    if (_solution == 0){
        _solution = new CCP::Solution(_instance);
//        connect(_solution, SIGNAL(finished()),this,SLOT(finishedAlgorithm()));
    }
//    if (_solution->isRunnig()){
//        statusBar()->showMessage("Allready running a algorithm.", 1000);
//        return;
//    }
    if (act){
        switch(act->data().toInt()){
        case CCP::HMeans:
            type = CCP::HMeans;
            //            setWindowTitle("HMeans");
            break;
        case CCP::JMeans:
            type = CCP::JMeans;
            //            setWindowTitle("JMeans");
            break;

        case CCP::Farthest:
            type = CCP::Farthest;
            //            setWindowTitle("Farthest");
            break;

        case CCP::Density:
            type = CCP::Density;
            //            setWindowTitle("Density");
            break;
        }
    }else{
        type = inType;
    }
    switch(type){
    case CCP::HMeans:
        //            type = CCP::HMeans;
        setWindowTitle("HMeans");
        break;
    case CCP::JMeans:
        //                type = CCP::JMeans;
        setWindowTitle("JMeans");
        break;

    case CCP::Farthest:
        //            type = CCP::Farthest;
        setWindowTitle("Farthest");
        break;

    case CCP::Density:
        //            type = CCP::Density;
        setWindowTitle("Density");
        break;
    }
    SolutionRunner::queue(_instance, type);
    //_solution->setAlgorithmToUse(type);
    //_solution->run();
}


void MainWindow::finishedAlgorithm(CCP::Solution * sol){
    if (! sol->isValid()){
        statusBar()->showMessage("Invalid  solution. ", 2000);
    }else{
        QString result = sol->algorithmName() + ",\t";
        result += QString::number(sol->getValue()) + ",\t";
        result += QString::number(sol->timeTaken()) + ",\t";
        result += QString::number(sol->iterations()) + ",\n";
        emit textResult(result);
    }
    emit newSolution(sol);
}

