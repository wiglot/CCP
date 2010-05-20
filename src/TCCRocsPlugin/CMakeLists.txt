

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

############ Path to CCP ########

include_directories( ../model ../algorithms )

########### Path to Rocs Core ##########

include_directories( /usr/include/rocs )


ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

set (Algorithms_CCP
    ../algorithms/HMeansCluster.cpp
    ../algorithms/JMeansCluster.cpp
    ../algorithms/densitycluster.cpp
    ../algorithms/farthestcluster.cpp
    ../algorithms/algorithmstruct.cpp
)
set (Algorithms_H     ../algorithms/algorithmstruct.h)

set (Model_CCP
../model/Cluster.cpp
../model/Distance.cpp
../model/Instance.cpp
../model/Point.cpp
../model/Position.cpp
../model/Solution.cpp
../model/SolutionImprovement.cpp
../model/SolutionRunner.cpp
../model/History.cpp
)
Set (TCCRun_SRC TCCrun.cpp )

qt4_automoc(${Algorithms_CCP})
QT4_WRAP_CPP(MOC_CPP ${Algorithms_H})

kde4_add_plugin(TCCrun ${TCCRun_SRC}  ${Model_CCP} ${Algorithms_CCP} )
target_link_libraries(TCCrun
			    ${KDE4_KDEUI_LIBS}
                            rocslib

		     )

install(TARGETS TCCrun  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES TCCrun.desktop  DESTINATION ${SERVICES_INSTALL_DIR})
