#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "viewcluster.h"
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDockWidget>
#include <Instance.h>
#include <Solution.h>
#include <readccp.h>
#include "RunData.h"

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
    QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
    dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|
                                Qt::RightDockWidgetArea);
    dockWidget->setWidget(run);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

    connect (this, SIGNAL(newInstance(CCP::Instance*)), centralWidget(), SLOT(setInstance(CCP::Instance*)));
    connect (this, SIGNAL(newSolution(CCP::Solution*)), centralWidget(), SLOT(setSolution(CCP::Solution*)));

    connect (this, SIGNAL(newSolution(CCP::Solution*)), run, SLOT(setData(CCP::Solution*)));
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
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    act = menu->addAction("Density",this,SLOT(runAlgorithm()));
    act->setData(CCP::Density);
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    act = menu->addAction("JMeans",this,SLOT(runAlgorithm()));
    act->setData(CCP::JMeans);
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_J));
    act = menu->addAction("HMeans",this,SLOT(runAlgorithm()));
    act->setData(CCP::HMeans);
    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
}

void MainWindow::openFile(){
    QFileDialog f(this);
    if (_instance){
        delete _instance;
    }
    f.setFilters(QStringList() << "Dat type (*.dat)"<<"Text files (*.txt)");
    if(f.exec()){
        QString filename = f.selectedFiles().at(0);
        QString filter = f.selectedFilter();
        qDebug() << filename << filter;
        if (filter == "Dat type (*.dat)"){
            _instance = readCCP::readLorenaEuclidian(filename);

        }else if (filter == "Text files (*.txt)"){
            _instance = readCCP::readSimpleTXT(filename);

        }
        new CCP::Distance(_instance);
        if (_solution){
            delete _solution;
        }
        _solution = 0;
        emit newInstance(_instance);

//    Instance * foo;
//    QApplication app(argc, argv);
//    if (argc > 1){
//        foo = readCCP::readLorenaEuclidian(argv[1]);
//    }else {
//          foo = readCCP::readSimpleTXT("instances/instance1.txt");
//    }
//
//  //   Distance * distance = new Distance(foo);
//
//    Solution * sol = new Solution(foo);
//    QTime time;
//    time.start();
//    sol->constructSolution(CCP::Density);
//  //  sol->constructSolution();
//    qDebug() << "Build time: "<< time.elapsed()/1000.0;
//    qDebug() << "Value: " << sol->getValue();
    }
}

void MainWindow::runAlgorithm(){
    QAction * act = qobject_cast<QAction*>(sender());
    if (_solution == 0){
        _solution = new CCP::Solution(_instance);
    }
    if (act){
        QTime time;
        time.start();
        switch(act->data().toInt()){
        case CCP::HMeans:
            _solution->constructSolution(CCP::HMeans);
            setWindowTitle("HMeans");
                break;
        case CCP::JMeans:
            _solution->constructSolution(CCP::JMeans);
            setWindowTitle("JMeans");
            break;

        case CCP::Farthest:
            _solution->constructSolution(CCP::Farthest);
            setWindowTitle("Farthest");
            break;

        case CCP::Density:
            _solution->constructSolution(CCP::Density);
            setWindowTitle("Density");
            break;
        }
        qDebug() << _solution->isValid();
        if (! _solution->isValid()){
            statusBar()->showMessage("Invalid  solution. ", 2000);
        }
        qDebug() << time.elapsed()/1000.0;
        qDebug() << "Value: " << _solution->getValue();
        emit newSolution(_solution);
    }
}


