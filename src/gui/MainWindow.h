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
   void runAlgorithm();
//    void kmeansAlgorithm();
//    void farAlgorithm();
//    void densityAlgorithm();
protected:
    void changeEvent(QEvent *e);
signals:
    void newInstance(CCP::Instance * ins);
    void newSolution(CCP::Solution * sol);
private:
    void setupAction();
    Ui::MainWindow *ui;
    CCP::Solution * _solution;
    CCP::Instance * _instance;
};

#endif // MAINWINDOW_H
