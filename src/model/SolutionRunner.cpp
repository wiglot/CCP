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

void SolutionRunner::queue(Instance *instance, HeuristicType type, bool improve){
    Solution * sol = new Solution(instance);
    sol->setAlgorithmToUse(type);
    SolutionRunner::New()->insert(sol, improve);
}

void SolutionRunner::queue(CCP::Solution *sol, CCP::ImprovementHeuristic type){
    sol->setImprovement(type);
    SolutionRunner::New()->insert(sol);
}

void SolutionRunner::run(){
    QPair <Solution *, bool> sol = next();
    while (sol.first){
        if (sol.first->isImprovement()){
            Solution * improved = new Solution(sol.first->getInstance());
            *improved = sol.first->improve();
            if (improved->isValid()){
                emit finished(improved);

            }else{
                emit finished(0);
                delete improved;
            }
        }else{
            sol.first->run();
            if (sol.first->isValid()){
                emit finished(sol.first);
                if(sol.second){
                    Solution * imp = new Solution(sol.first->getInstance());
                    sol.first->setImprovement(CCP::HillClimbInterchange);
                    *imp = sol.first->improve();
                    if (imp->isValid()){
                        emit finished(imp);
                    }else{
                        delete imp;
                    }
                    imp = new Solution(sol.first->getInstance());
                    sol.first->setImprovement(CCP::HillClimbShift);
                    *imp = sol.first->improve();
                    if (imp->isValid()){
                        emit finished(imp);
                    }else{
                        delete imp;
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

