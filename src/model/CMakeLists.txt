
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../algorithms)


set (Model_CCP
    Cluster.cpp
    Distance.cpp
    Instance.cpp
    Point.cpp
    Position.cpp
    Solution.cpp
    SolutionImprovement.cpp
    SolutionRunner.cpp
    History.cpp
)

set (Model_H SolutionRunner.h)

qt4_automoc(${Model_CCP})
QT4_WRAP_CPP(MOC_CPP ${Model_H})

add_library(CCPModelLib SHARED ${Model_CCP} ${MOC_CPP})

link_libraries(CCPModelLib ${QT_QT_LIBRARY} ${QT_QTGUI_LIBRARY} ${CCPAlgorithms})

# set_target_properties( CCPModelLib  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )

#install( TARGETS CCPModelLib  ${INSTALL_TARGETS_DEFAULT_ARGS} )


