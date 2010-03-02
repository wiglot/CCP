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

CCP::Solution * SolutionRunner::next(){
    Solution * sol = 0;
    readQueue.lock();
    if (solQueue.count() > 0){
      sol = solQueue.dequeue();
    }
    readQueue.unlock();
    return sol;
}

void SolutionRunner::insert(CCP::Solution * sol){

    readQueue.lock();
    solQueue.enqueue(sol);
    readQueue.unlock();

    if (running.tryLock()){
        this->start();
    }

}

void SolutionRunner::queue(Instance *instance, HeuristicType type){
    Solution * sol = new Solution(instance);
    sol->setAlgorithmToUse(type);
    SolutionRunner::New()->insert(sol);
}

void SolutionRunner::run(){
    Solution * sol = next();
    while (sol){
        sol->run();
        emit finished(sol);
        sol = next();
    }
    running.unlock();
}

