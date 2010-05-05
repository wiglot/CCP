#ifndef RUNBATCH_H
#define RUNBATCH_H

#include <QDockWidget>
#include <Solution.h>


namespace Ui {
    class RunBatch;
}

class RunBatch : public QDockWidget {
    Q_OBJECT
public:
    explicit RunBatch(QWidget *parent = 0);
    ~RunBatch();

protected:
    void changeEvent(QEvent *e);

signals:
    void runAlgorithm(CCP::HeuristicType type, bool improve);

private slots:
    void run();
private:
    Ui::RunBatch *ui;
};

#endif // RUNBATCH_H
