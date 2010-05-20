#ifndef SOLUTIONRUNNER_H
#define SOLUTIONRUNNER_H

#include "model_global.h"

#include <QObject>
#include "Instance.h"
#include "Solution.h"
#include <QQueue>
#include <QPair>
#include <QMutex>
#include <QThread>

class /*CCPModelLib_EXPORT*/ SolutionRunner : public QThread
{
Q_OBJECT
    QQueue < QPair<CCP::Solution*, bool> > solQueue;

    QMutex readQueue;
    QMutex running;
    QPair<CCP::Solution*, bool> next();
    void insert(CCP::Solution * sol, bool improve = false);

    static SolutionRunner * inst;

public:
    explicit SolutionRunner(QObject *parent = 0);
    void run();

signals:
    void finished(CCP::Solution * sol);

public slots:
    static void queue(CCP::Instance *instance, CCP::HeuristicType type, bool improve = false);
    static void queue(CCP::Solution *sol, CCP::ImprovementHeuristic type);
    static SolutionRunner * New();
};

#endif // SOLUTIONRUNNER_H
