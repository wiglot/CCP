#ifndef SOLUTIONIMPROVEMENT_H
#define SOLUTIONIMPROVEMENT_H

#include "model_global.h"
#include <QPair>
#include "Cluster.h"

class QString;
//#include "Solution.h"

namespace CCP
{
class Solution;

class /*CCPModelLib_EXPORT*/ SolutionImprovement
{

private:
    SolutionImprovement();
public:
    static CCP::Solution * hillClimbShift ( CCP::Solution * sol, int K = 0 );
    static CCP::Solution * hillClimbInterchange ( CCP::Solution * sol, int K = 0, int Q = 0 );

    static CCP::Solution * SAShift ( CCP::Solution * sol );
    static CCP::Solution * SAInterchange ( CCP::Solution * sol );

    static CCP::Solution * WaveShift ( CCP::Solution* solution, const double& percNodes, const double& percClusters, const double& overload, const int& version );


    static CCP::Solution * improve ( CCP::Solution * sol, const ImprovementHeuristic type );

    static QVector<InterchangeResult> improveCluster_v1 ( Solution *sol, CCP::Cluster* clusterToFeasible , QPair<Cluster*, int> avoidShift );

    static QVector<InterchangeResult> improveCluster_v1_1 ( Solution *sol, CCP::Cluster* clusterToFeasible , QPair<Cluster*, int> avoidShift );

    static QVector<InterchangeResult> makeFeasible_v1 ( CCP::Solution* sol, CCP::Cluster* clusterToFeasible, QPair< CCP::Cluster*, int > avoidShift );
    static QVector<InterchangeResult> makeFeasible_v1_1 ( CCP::Solution* sol, CCP::Cluster* clusterToFeasible, QPair< CCP::Cluster*, int > avoidShift );

    static QString text ( ImprovementHeuristic type );
};
}
#endif // SOLUTIONIMPROVEMENT_H
