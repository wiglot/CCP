#ifndef MODEL_GLOBAL_H
#define MODEL_GLOBAL_H
#include <QtCore/QtGlobal>
namespace CCP{
    enum PointType {
        Center,
        Consumer
    };

    enum HeuristicType {
        Density,
        Farthest,
        HMeans,
        JMeans,
        RandonDensity,
        DensityHMeans,
        DensityJMeans
    };

    enum ImprovementHeuristic {
        HillClimbShift,
        HillClimbInterchange,
        SimulatedAnnelingShift,
        SimulatedAnnelingInterchange
    };
}
// #ifndef CCPModelLib_EXPORT
// # if defined(MAKE_CCPModelLib_LIB)
// // We are building this library
// #    define CCPModelLib_EXPORT Q_DECL_EXPORT
// # else
// // We are using this library
// #    define CCPModelLib_EXPORT Q_DECL_IMPORT
// # endif
// #endif
//
// # ifndef CCPModelLib_EXPORT_DEPRECATED
// #  define CCPModelLib_EXPORT_DEPRECATED Q_DECL_DEPRECATED CCPModelLib_EXPORT
// # endif

#endif // MODEL_GLOBAL_H
