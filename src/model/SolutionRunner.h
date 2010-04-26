#ifndef SOLUTIONRUNNER_H
#define SOLUTIONRUNNER_H

#include "model_global.h"

#include <QObject>
#include "Instance.h"
#include "Solution.h"
#include <QQueue>
#include <QMutex>
#include <QThread>

class CCPModelLib_EXPORT SolutionRunner : public QThread
{
Q_OBJECT
    QQueue <CCP::Solution*> solQueue;

    QMutex readQueue;
    QMutex running;
    CCP::Solution * next();
    void insert(CCP::Solution * sol);

    static SolutionRunner * inst;

public:
    explicit SolutionRunner(QObject *parent = 0);
    void run();

signals:
    void finished(CCP::Solution * sol);

public slots:
    static void queue(CCP::Instance *instance, CCP::HeuristicType type);
    static void queue(CCP::Solution *sol, CCP::ImprovementHeuristic type);
    static SolutionRunner * New();
};

#endif // SOLUTIONRUNNER_H
