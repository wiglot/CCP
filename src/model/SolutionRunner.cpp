#include "SolutionRunner.h"
#include <QQueue>

using namespace CCP;
SolutionRunner * SolutionRunner::inst = 0;

SolutionRunner::SolutionRunner(QObject *parent) :
        QThread(parent)
{

}

SolutionRunner * SolutionRunner::New(){
    if (SolutionRunner::inst == 0){
        SolutionRunner::inst = new SolutionRunner();
    }
    return SolutionRunner::inst;
}

QPair<Solution*, bool> SolutionRunner::next(){
    QPair<Solution*, bool> sol(0,false);
    readQueue.lock();
    if (solQueue.count() > 0){
        sol = solQueue.dequeue();
    }
    readQueue.unlock();
    return sol;
}

void SolutionRunner::insert(CCP::Solution * sol, bool improve){
    QPair < Solution*, bool> imp(sol, improve);
    readQueue.lock();
    solQueue.enqueue(imp);
    readQueue.unlock();

    if (running.tryLock()){
        this->start();
    }

}

void SolutionRunner::queue(Instance *instance, HeuristicType type, bool improve, bool useThread){
    Solution * sol = new Solution(instance);
    sol->setAlgorithmToUse(type);
    if (useThread){
      SolutionRunner::New()->insert(sol, improve);
    }else{
      New()->running.lock();
      QPair < Solution*, bool> imp(sol, improve);
      New()->solQueue.enqueue(imp);
      New()->run();
    }
}

void SolutionRunner::queue(CCP::Solution *sol, CCP::ImprovementHeuristic type){
    sol->setImprovement(type);
    SolutionRunner::New()->insert(sol);
}

void SolutionRunner::run(){
    QPair <Solution *, bool> sol = next();
    while (sol.first){
        if (sol.first->isImprovement()){
            if (Solution * improved = sol.first->improve()){
                if (improved->isValid()){
                    emit finished(improved);

                }else{
                    emit finished(0);
                    improved->deleteLater();
                }
            }
        }else{
            sol.first->run();
            if (sol.first->isValid()){
                emit finished(sol.first);
                if(sol.second){
                    sol.first->setImprovement(CCP::HillClimbInterchange);
                    Solution * imp = sol.first->improve();
                    if (imp->isValid()){
                        emit finished(imp);
                    }else{
                        imp->deleteLater();;
                    }
                    sol.first->setImprovement(CCP::HillClimbShift);
                    imp = sol.first->improve();
                    if (imp->isValid()){
                        emit finished(imp);
                    }else{
                        imp->deleteLater();;
                    }
                }
            }else{
                emit finished(0);
                delete sol.first;
            }
        }
        sol = next();

    }
    running.unlock();
}

