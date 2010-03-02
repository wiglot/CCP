#include "SolutionImprovement.h"
#include "Solution.h"
#include "Instance.h"
#include "Cluster.h"

using namespace CCP;

SolutionImprovement::SolutionImprovement( Solution &sol):_solution(sol)
{

}

Solution SolutionImprovement::hillClimb(){
//    Solution bestSol = _solution;
//    double bestValue = 1e10;
//    bool foundBetter = false;
//    Instance * inst = _solution.instance();
//
//    do{
//        Solution* tmpSol = new Solution(inst);
//        *tmpSol = bestSol;
//
//        for (int center= 0; center < tmpSol->instance()->numCenters(); ++center){
//            Cluster * origin = tmpSol->cluster(center);
//            for (int points = 0; points < origin->numPoints(); ++points){
//                int newCenter = center;
//                double better = 0.0;
//                for (int center2= 0; center2 < tmpSol->instance()->numCenters(); ++center2){
//                    if (center != center2){
//                        Cluster * dest = tmpSol->cluster(center2);
//                        InterchangeResult result = origin->interchange(origin->getPoint(points),dest);
//                        if (result.isValid()){
//                            if (result.changeInValue() < better){
//                                better = result.changeInValue();
//                                newCenter = center2;
//                            }
//                        }
//                        result.undo();
//                    }
//                }
//                if (newCenter != center){
//                    origin->interchange(origin->getPoint(points), tmpSol->cluster(newCenter));
//
//                }
//            }
//        }
//
//        if (tmpSol->getValue() < bestValue){
//
//            bestSol = *tmpSol;
//            foundBetter = true;
//        }
//        delete tmpSol;
//
//    }while (foundBetter);
//    return bestSol;
}
