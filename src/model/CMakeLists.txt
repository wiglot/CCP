
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../algorithms)


set (Model_CCP Cluster.cpp Distance.cpp Instance.cpp Point.cpp Position.cpp Solution.cpp)

set (Model_H Solution.h)

qt4_automoc(${Model_CCP})
QT4_WRAP_CPP(MOC_CPP ${Model_H})

add_library(CCPModelLib SHARED ${Model_CCP} ${MOC_CPP})

link_libraries(CCPModelLib ${QT_QT_LIBRARY} ${QT_QTGUI_LIBRARY} ${CCPAlgorithms})
