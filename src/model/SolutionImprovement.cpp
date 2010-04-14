#include "SolutionImprovement.h"
#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"

#include <QDebug>

using namespace CCP;

SolutionImprovement::SolutionImprovement( )
{
    //    _solution = sol;
}

Solution  SolutionImprovement::hillClimbShift( Solution & sol, int K){
    Instance * inst = sol.instance();
    Solution bestSol(inst);
    bestSol = sol;
    double bestValue = sol.getValue();
    bool foundBetter = false;
    int count = 0;

    do{
        ++count;

        Solution* tmpSol = new Solution(inst);
        *tmpSol = bestSol;

        for (int center= 0; center < tmpSol->instance()->numCenters(); ++center){
            Cluster * origin = tmpSol->cluster(center);
            for (int points = 0; points < origin->numPoints(); ++points){
                int newCenter = center;
                double better = 0.0;
                for (int center2= 0; center2 < tmpSol->instance()->numCenters(); ++center2){
                    if (center != center2){
                        Cluster * dest = tmpSol->cluster(center2);
                        InterchangeResult result = origin->shift(origin->getPoint(points),dest);
                        if (result.isValid()){
                            if (result.changeInValue() < better){
                                better = result.changeInValue();
                                newCenter = center2;
                            }
                        }
                        result.undo();
                    }
                }
                if (newCenter != center){
                    origin->shift(origin->getPoint(points), tmpSol->cluster(newCenter));

                }
            }
        }


        if (bestSol.getValue() < bestValue){
            bestValue = bestSol.getValue();
            bestSol = *tmpSol;
            foundBetter = true;
        }else{
            foundBetter = false;
        }
        delete tmpSol;

    }while (foundBetter);
    bestSol.setIterations(count);
    return bestSol;
}


Solution  SolutionImprovement::hillClimbInterchange(Solution & sol, int K, int Q){
    Instance * inst = sol.instance();
    Solution bestSol(inst);
    bestSol = sol;
    int count = 0;
    double bestValue = sol.getValue();
    bool foundBetter = false;
    InterchangeResult bestMove(0,0,0,0);
    Cluster * cluster;
    Cluster * myCluster;
//    int  m_q;
    QMap <double, Cluster*> nearClusters;

    int count_k, count_q;

    if (K == 0){
        K = inst->numCenters() * 0.3;
    }
    if (Q == 0){
        Q = (inst->numPoints()/inst->numCenters()) * 0.5;
    }
    do{
        ++count;
        //        Solution* tmpSol = new Solution(inst);
        //        *tmpSol = bestSol;
        double better = 0.0;
        for (int i = 0 ; i < inst->numPoints(); i++){
            nearClusters.clear();
            for (int j = 0;  j <  inst->numCenters(); ++j){

                if (bestSol.cluster(j)->contains(inst->point(i))){
                    myCluster = bestSol.cluster(j);
                }else{
                    nearClusters.insert(inst->distance(i, bestSol.centerOfCluster(j)->index()), bestSol.cluster(j) );
                }
            }

            for (count_k = 0; ( count_k < K ) && (count_k < nearClusters.count()) ; count_k++){
                cluster = nearClusters.values().at(count_k);//

                QMap<double, Point *> nearPoints;
                for ( int j =0; j < cluster->numPoints(); ++j){
                    nearPoints.insert(inst->distance(i, cluster->getPoint(j)->index()), cluster->getPoint(j) );
                }
                nearPoints.insert(inst->distance(i, cluster->getCenter()->index()), cluster->getCenter());

                for (count_q =0; count_q < Q && count_q < nearPoints.values().count();  ++count_q){
                    Point * p = nearPoints.values()[count_q];
                    InterchangeResult result = myCluster->interchange(inst->point(i), p ,cluster);

                    if (result.isValid()){
                        if (result.changeInValue() < better){
                            qDebug() << result.changeInValue();
                            better = result.changeInValue();
                            result.undo();
                            bestMove = result;
                        }
                    }
                    result.undo();

                }

            }
        }




        qDebug() << "Applying best Move.";
        bestMove.redo();

        //qDebug() << tmpSol->getValue() << bestValue;
        if (bestSol.getValue() < bestValue){
            bestValue = bestSol.getValue();
//            bestSol = *tmpSol;
            foundBetter = true;
        }else{
            foundBetter = false;
        }
//        delete tmpSol;

    }while (foundBetter);

    return bestSol;
}

Solution  SolutionImprovement::SAShift(Solution & sol){
    Instance * inst = sol.instance();
    Solution bestSol(inst);
    bestSol = sol;


    return bestSol;
}

Solution  SolutionImprovement::SAInterchange(Solution & sol){
    Instance * inst = sol.instance();
    Solution bestSol(inst);
    bestSol = sol;

    return bestSol;
}


CCP::Solution SolutionImprovement::improve(CCP::Solution & sol, const ImprovementHeuristic type){
    switch (type){
    case CCP::HillClimbShift:
        return hillClimbShift(sol);
    case CCP::HillClimbInterchange:
        return hillClimbInterchange(sol);
    case CCP::SimulatedAnnelingShift:
        return SAShift(sol);
    case CCP::SimulatedAnnelingInterchange:
        return SAInterchange(sol);
    }

}

QString SolutionImprovement::text(ImprovementHeuristic type){
    switch (type){
    case HillClimbShift: return QString("Hill Climb with Shift");
    case HillClimbInterchange: return QString("Hill Climb with Interchange");
    case SimulatedAnnelingShift: return QString("SA with Shift");
    case SimulatedAnnelingInterchange: return QString("SA with Interchange");
    }
}
