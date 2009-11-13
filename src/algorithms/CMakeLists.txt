
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../model)


set (Algorithms_CCP densitycluster.cpp farthestcluster.cpp algorithmstruct.cpp)

qt4_automoc(${Algorithms_CCP})


add_library(CCPAlgorithms SHARED ${Algorithms_CCP})

link_libraries(CCPModelLib ${QT_QT_LIBRARY} ${CCPModelLib})