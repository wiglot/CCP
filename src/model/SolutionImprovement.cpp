#include "SolutionImprovement.h"
#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"

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
