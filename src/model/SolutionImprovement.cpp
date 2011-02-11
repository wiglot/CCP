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

Solution  SolutionImprovement::hillClimbShift ( Solution & sol, int K )
{
    Instance * inst = sol.instance();
    Solution bestSol ( inst );
    bestSol = sol;
    double bestValue = sol.getValue();
    bool foundBetter = false;
    int count = 0;

    do
    {
        ++count;

        Solution* tmpSol = new Solution ( inst );
        *tmpSol = bestSol;

        for ( int center= 0; center < tmpSol->instance()->numCenters(); ++center )
        {
            Cluster * origin = tmpSol->cluster ( center );
            for ( int points = 0; points < origin->numPoints(); ++points )
            {
                int newCenter = center;
                double better = 0.0;
                for ( int center2= 0; center2 < tmpSol->instance()->numCenters(); ++center2 )
                {
                    if ( center != center2 )
                    {
                        Cluster * dest = tmpSol->cluster ( center2 );
                        InterchangeResult result = origin->shift ( origin->getPoint ( points ),dest );
                        if ( result.isValid() )
                        {
                            if ( result.changeInValue() < better )
                            {
                                better = result.changeInValue();
                                newCenter = center2;
                            }
                        }
                        result.undo();
                    }
                }
                if ( newCenter != center )
                {
                    origin->shift ( origin->getPoint ( points ), tmpSol->cluster ( newCenter ) );

                }
            }
        }


        if ( ( bestValue - tmpSol->getValue() ) > 0.001 )
        {
            bestValue = bestSol.getValue();
            bestSol = *tmpSol;
            foundBetter = true;
        }
        else
        {
            foundBetter = false;
        }
        delete tmpSol;

    }
    while ( foundBetter && count < 100 );
    bestSol.setIterations ( count );
    return bestSol;
}


Solution  SolutionImprovement::hillClimbInterchange ( Solution & sol, int K, int Q )
{
    Instance * inst = sol.instance();
    Solution bestSol ( inst );
    bestSol = sol;
    int count = 0;
    double bestValue = sol.getValue();
    bool foundBetter = false;
    InterchangeResult bestMove ( 0,0,0,0 );
    Cluster * cluster;
    Cluster * myCluster = 0;
//    int  m_q;
    QMap <double, Cluster*> nearClusters;

    int count_k, count_q;

    if ( K == 0 )
    {
        K = inst->numCenters() * 0.3;
    }
    if ( Q == 0 )
    {
        Q = ( inst->numPoints() /inst->numCenters() ) * 0.5;
    }
    do
    {
        ++count;
        //        Solution* tmpSol = new Solution(inst);
        //        *tmpSol = bestSol;
        double better = 0.0;
        for ( int i = 0 ; i < inst->numPoints(); i++ )
        {
            nearClusters.clear();
            for ( int j = 0;  j <  inst->numCenters(); ++j )
            {

                if ( bestSol.cluster ( j )->contains ( inst->point ( i ) ) )
                {
                    myCluster = bestSol.cluster ( j );
                }
                else
                {
                    nearClusters.insert ( inst->distance ( i, bestSol.centerOfCluster ( j )->index() ), bestSol.cluster ( j ) );
                }
            }

            for ( count_k = 0; ( count_k < K ) && ( count_k < nearClusters.count() ) ; count_k++ )
            {
                cluster = nearClusters.values().at ( count_k );//

                QMap<double, Point *> nearPoints;
                for ( int j =0; j < cluster->numPoints(); ++j )
                {
                    nearPoints.insert ( inst->distance ( myCluster->getCenter()->index(), cluster->getPoint ( j )->index() ), cluster->getPoint ( j ) );
                }
                nearPoints.insert ( inst->distance ( myCluster->getCenter()->index(), cluster->getCenter()->index() ), cluster->getCenter() );

                for ( count_q =0; count_q < Q && count_q < nearPoints.values().count();  ++count_q )
                {
                    Point * p = nearPoints.values() [count_q];
                    InterchangeResult result = myCluster->interchange ( inst->point ( i ), p ,cluster );

                    if ( result.isValid() )
                        if ( result.changeInValue() < better )
                        {
                            qDebug() << result.changeInValue();
                            better = result.changeInValue();
                            result.undo();
                            bestMove = result;
                        }
                    result.undo();

                }

            }
        }

        qDebug() << "Applying best Move.";
        bestMove.redo();

        //qDebug() << tmpSol->getValue() << bestValue;
        if ( qAbs ( bestSol.getValue() - bestValue ) > 0.0001 )
        {
            bestValue = bestSol.getValue();
//            bestSol = *tmpSol;
            foundBetter = true;
        }
        else
        {
            foundBetter = false;
        }
//        delete tmpSol;

    }
    while ( foundBetter && count < 100 );

    return bestSol;
}

Solution  SolutionImprovement::SAShift ( Solution & sol )
{
    Instance * inst = sol.instance();
    Solution bestSol ( inst );
    bestSol = sol;

    return bestSol;
}

Solution  SolutionImprovement::SAInterchange ( Solution & sol )
{
    Instance * inst = sol.instance();
    Solution bestSol ( inst );
    bestSol = sol;

    return bestSol;
}

QVector<InterchangeResult> SolutionImprovement::makeFeasible ( Solution &sol, CCP::Cluster* clusterToFeasible , QPair<Cluster*, int> avoidShift )
{
    QVector<InterchangeResult> ret;
    Instance * inst = sol.instance();
    QMultiMap<double, int> distances;
    for ( int i = 0; i < clusterToFeasible->numPoints(); ++i )
        distances.insert ( inst->distance ( clusterToFeasible->getPoint ( i )->index(), clusterToFeasible->getCenter()->index() ),
                           clusterToFeasible->getPoint(i)->index() );
    distances.insert(0, clusterToFeasible->getCenter()->index());
    int i = distances.size();
    while ( clusterToFeasible->remainCapacity() < 0 && i > 0)
    {
        --i;
        int node = distances.values().at ( i );
        double dist = 1.0e6;
        int clust = -1;
        for ( int j = 0; j < inst->numCenters(); ++j )
        {
            if ( (sol.cluster ( j ) != avoidShift.first) ^ (node != avoidShift.second) )
                if ( inst->point(node)->demand() <= sol.cluster(j)->remainCapacity() &&  inst->distance ( node, sol.centerOfCluster ( j )->index() ) < dist )
                {
                    dist = inst->distance ( node, sol.centerOfCluster ( j )->index() );
                    clust = j;
                }
        }
        if (clust == -1)
            continue;
        InterchangeResult result =  clusterToFeasible->shift ( inst->point ( node ), sol.cluster ( clust ) );
        if (result.isValid())
            ret.append(result);

        qDebug() << result.changeInValue();
    }
    return ret;
}


Solution SolutionImprovement::WaveShift ( Solution& solution, const double& percNodes, const double& percClusters, const double& overload )
{

    Instance *inst = solution.getInstance();
    Solution workSol(inst);
    workSol = solution;

    QHash <int, QMultiMap<double, int> > nearCluster;
    QMultiMap<double, QPair<int, int> > farFromCenter;

    int count = 0;
    do {
        workSol.setIterations(count++);
        QHash <int,int> nodesCluster;

        for ( int i = 0; i < inst->numPoints(); ++i )
        {
            QMultiMap<double, int> clusters;
            for ( int j = 0; j < inst->numCenters(); ++j )
                if ( workSol.cluster ( j )->contains ( inst->point ( i ) ) ) {
                    nodesCluster.insert ( i,j );
                    farFromCenter.insert(inst->distance ( workSol.centerOfCluster ( j )->index(), i ), QPair<int, int> (i, j));
                } else
                    clusters.insert(inst->distance ( workSol.centerOfCluster ( j )->index(), i ), j);


            nearCluster.insert(i, clusters);
        }
        if (nearCluster.isEmpty())
            return workSol;
        QMultiMap <qreal, QVector<InterchangeResult>*  > resultList;
        for ( int i = farFromCenter.size()-1; i > ( farFromCenter.size() * ( 1-percNodes ) ); --i )
        {
            int node = farFromCenter.values().at ( i ).first;
            Cluster * clustOrigin = workSol.cluster ( nodesCluster.value ( node ) );
            for (int j = 0; j < nearCluster.value(node).size()*percClusters; ++j ) {
                QVector<InterchangeResult> *results = new QVector<InterchangeResult>;
                Cluster* cluster = workSol.cluster ( nearCluster.value(node).values().at ( j ));
                if (inst->distance(node, clustOrigin->getCenter()->index()) <= nearCluster.keys().at(j))
                    continue;
                InterchangeResult result =  clustOrigin->shift ( inst->point ( node ), cluster, overload );
                results->append(result);
                if ( cluster->remainCapacity() < 0 )
                {
                    qDebug() << "Infactivel.";
                    (*results)+= makeFeasible( workSol, cluster, QPair<Cluster*,int> ( clustOrigin, node ) );
                    if (cluster->remainCapacity() < 0) {
                        qDebug() << "Still infeasible. rejecting move.";
                        foreach (InterchangeResult r, (*results))
                          r.forceUndo();
                        continue;
                    }
                }
                if (results->isEmpty()) {
                    delete results;
                    break;
                }

                qreal red = 0.0;
                for (int i = results->size()-1; i >= 0;--i) {
//                 QMutableVectorIterator<InterchangeResult> i(*results);
//                 i.toBack();
//                 while (i.hasPrevious()) {
                    red += results->at(i).changeInValue();
                    results->operator[](i).forceUndo();
                }
//                 qDebug() << "This move prodeccs a gain of " << red;
                if (red < 0.0)
                    resultList.insert(red, results);
                else
                    delete results;
            }
        }
        if (resultList.isEmpty())
            return workSol;
        qDebug() << "Applying results: " << resultList.keys();
        QVector<InterchangeResult>* result = resultList.values().first();
        for (int i = 0 ; i < result->size(); ++i)
            result->operator[](i).redo();
//         QMutableVectorIterator<InterchangeResult> i(*(resultList.values().first()));
//         while (i.hasNext())
//             i.next().redo();
        qDeleteAll( resultList.values() );
        resultList.clear();
    }
    while ( 1 );
    return workSol;
}



CCP::Solution SolutionImprovement::improve ( CCP::Solution & sol, const ImprovementHeuristic type )
{
    switch ( type )
    {
    case CCP::HillClimbShift:
        return hillClimbShift ( sol );
    case CCP::HillClimbInterchange:
        return hillClimbInterchange ( sol );
    case CCP::SimulatedAnnelingShift:
        return SAShift ( sol );
    case CCP::SimulatedAnnelingInterchange:
        return SAInterchange ( sol );
    case CCP::HillClimbShiftWithOveload:
        return WaveShift(sol, 0.2, 0.4, 2.0);
    }

}

QString SolutionImprovement::text ( ImprovementHeuristic type )
{
    switch ( type )
    {
    case HillClimbShift:
        return QString ( "Hill Climb with Shift" );
    case HillClimbInterchange:
        return QString ( "Hill Climb with Interchange" );
    case SimulatedAnnelingShift:
        return QString ( "SA with Shift" );
    case SimulatedAnnelingInterchange:
        return QString ( "SA with Interchange" );
    case CCP::HillClimbShiftWithOveload:
        return QString("Wave Shift");
    }
}
