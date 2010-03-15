#ifndef SOLUTIONIMPROVEMENT_H
#define SOLUTIONIMPROVEMENT_H

#include "Solution.h"

namespace CCP{



class SolutionImprovement
{

private:
    SolutionImprovement();
public:
    static CCP::Solution  hillClimbShift(CCP::Solution & sol);
    static CCP::Solution  hillClimbInterchange(CCP::Solution & sol);

    static CCP::Solution  SAShift(CCP::Solution & sol);
    static CCP::Solution  SAInterchange(CCP::Solution & sol);
};
}
#endif // SOLUTIONIMPROVEMENT_H
