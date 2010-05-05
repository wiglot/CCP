#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Solution.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
   void openFile();
   void runAlgorithm(CCP::HeuristicType type = CCP::Farthest, bool improve = false );
//    void kmeansAlgorithm();
//    void farAlgorithm();
//    void densityAlgorithm();
protected:
    void changeEvent(QEvent *e);
signals:
    void newInstance(CCP::Instance * ins);
    void newSolution(CCP::Solution * sol);
    void textResult(QString result);

    void closing();

private slots:
    /** when end of run any algorithm, this method is called to append solution to output.*/
    void finishedAlgorithm(CCP::Solution * sol);
    /** Just whant to show the solution, but not append to exit.*/
    void showSolution(CCP::Solution* sol);
    void improveSolution();
    void closeInstance();
private:
    void setupAction();
    Ui::MainWindow *ui;
    CCP::Solution * _solution;
    CCP::Instance * _instance;
};

#endif // MAINWINDOW_H
