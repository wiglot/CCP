
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../model)


set (Algorithms_CCP HMeansCluster.cpp JMeansCluster.cpp densitycluster.cpp farthestcluster.cpp algorithmstruct.cpp)
set (Algorithms_H algorithmstruct.h)
qt4_automoc(${Algorithms_CCP})
QT4_WRAP_CPP(MOC_CPP ${Algorithms_H})

add_library(CCPAlgorithms SHARED ${Algorithms_CCP} ${MOC_CPP})

#link_libraries(CCPModelLib ${QT_QT_LIBRARY} CCPModelLib )
