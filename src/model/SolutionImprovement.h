#ifndef SOLUTIONIMPROVEMENT_H
#define SOLUTIONIMPROVEMENT_H

namespace CCP{
    class Solution;



class SolutionImprovement
{

private:
     CCP::Solution & _solution;
public:
    SolutionImprovement( CCP::Solution & sol);

    CCP::Solution  hillClimb();

};
}
#endif // SOLUTIONIMPROVEMENT_H
