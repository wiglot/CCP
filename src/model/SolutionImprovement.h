#ifndef SOLUTIONIMPROVEMENT_H
#define SOLUTIONIMPROVEMENT_H

#include "model_global.h"

class QString;
//#include "Solution.h"

namespace CCP{

class Solution;



class /*CCPModelLib_EXPORT*/ SolutionImprovement
{

private:
    SolutionImprovement();
public:
    static CCP::Solution  hillClimbShift(CCP::Solution & sol, int K = 0);
    static CCP::Solution  hillClimbInterchange(CCP::Solution & sol, int K = 0, int Q = 0 );

    static CCP::Solution  SAShift(CCP::Solution & sol);
    static CCP::Solution  SAInterchange(CCP::Solution & sol);

    static CCP::Solution improve(CCP::Solution & sol, const ImprovementHeuristic type);

    static QString text(ImprovementHeuristic type);
};
}
#endif // SOLUTIONIMPROVEMENT_H
