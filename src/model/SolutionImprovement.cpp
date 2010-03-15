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

Solution  SolutionImprovement::hillClimbShift( Solution & sol){
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

        if (tmpSol->getValue() < bestValue){
            bestValue = tmpSol->getValue();
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


Solution  SolutionImprovement::hillClimbInterchange(Solution & sol){
    Instance * inst = sol.instance();
    Solution bestSol(inst);
    bestSol = sol;
    int count = 0;
    double bestValue = sol.getValue();
    bool foundBetter = false;
    InterchangeResult bestMove(0,0,0,0);

    do{
        ++count;
        Solution* tmpSol = new Solution(inst);
        *tmpSol = bestSol;
        double better = 0.0;
        for (int center= 0; center < tmpSol->instance()->numCenters(); ++center){
            Cluster * origin = tmpSol->cluster(center);
            for (int center2= 0; center2 < tmpSol->instance()->numCenters(); ++center2){
                if (center != center2){

                    Cluster * dest = tmpSol->cluster(center2);
                    for (int point1 = 0; point1 < origin->numPoints(); ++point1){
                        for (int point2 = 0; point2 < dest->numPoints(); ++point2){
                            Point * p1 = origin->getPoint(point1);
                            Point * p2 = dest->getPoint(point2);

                            InterchangeResult result = origin->interchange(p1,p2,dest);

                            if (result.isValid()){
                                if (result.changeInValue() < better){
                                    qDebug() << result.changeInValue();
                                    better = result.changeInValue();
                                    result.undo();
                                    bestMove = result;
                                }else{
                                    result.undo();
                                }
                            }

                        }
                    }
                }
            }
        }

        bestMove.redo();

        qDebug() << tmpSol->getValue() << bestValue;
        if (tmpSol->getValue() < bestValue){
            bestValue = tmpSol->getValue();
            bestSol = *tmpSol;
            foundBetter = true;
        }else{
            foundBetter = false;
        }
        delete tmpSol;

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
    case CCP::SAShift:
        return SAShift(sol);
    case CCP::SAInterchange:
        return SAInterchange(sol);
    }

}
