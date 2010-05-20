
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../src/model ../src/io)

set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/..)

set(CCPTest_SRCS CCPTest.cpp)
set(CCPModel_SRCS ccpmodel_test.cpp )
set(CCPDistance_SRCS CCPDistance.cpp )
set(CCPSolution_SRCS CCPSolution.cpp)
set(CCPRead_SRCS CCPRead.cpp)

qt4_automoc(${CCPTest_SRCS})
qt4_automoc(${CCPModel_SRCS})
qt4_automoc(${CCPDistance_SRCS})
qt4_automoc(${CCPSolution_SRCS})
qt4_automoc(${CCPRead_SRCS})


add_executable(CCPTest ${CCPTest_SRCS})
add_executable(CCPModel ${CCPModel_SRCS})
add_executable(CCPDistance ${CCPDistance_SRCS})
add_executable(CCPSolution ${CCPSolution_SRCS})
add_executable(CCPRead ${CCPRead_SRCS})

add_test(CCPTest CCPTest)
add_test(CCPModel CCPModel)
add_test(CCPDistance CCPDistance)
add_test(CCPSolution CCPSolution)
add_test(CCPRead CCPRead)

target_link_libraries(CCPTest ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms CCPIOLib)
target_link_libraries(CCPModel ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPDistance ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPSolution ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms CCPIOLib)
target_link_libraries(CCPRead ${QT_QTTEST_LIBRARY} CCPModelLib CCPIOLib CCPAlgorithms)


########## CCPCluster_Test #############
set(ClusterTest CCPCluster_Test.cpp)

qt4_automoc (${ClusterTest})

add_executable(CCPCluster ${ClusterTest})

add_test(CCPCluster CCPCluster)

target_link_libraries(CCPCluster ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)



########## CCPSolutionImprovement_Test #############
set(SolutionImprovementTest CCPSolutionImprovement_Test.cpp)

qt4_automoc (${SolutionImprovementTest})

add_executable(CCPSolutionImprovement ${SolutionImprovementTest})

add_test(CCPSolutionImprovement CCPSolutionImprovement)

target_link_libraries(CCPSolutionImprovement ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)


########## CCPHistory_Test #############
set(CCPHistory_SRC CCPHistory.cpp)

qt4_automoc (${CCPHistory_SRC})

add_executable(CCPHistory ${CCPHistory_SRC})

add_test(CCPHistory CCPHistory)

target_link_libraries(CCPHistory ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)