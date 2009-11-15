
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

target_link_libraries(CCPTest ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPModel ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPDistance ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPSolution ${QT_QTTEST_LIBRARY} CCPModelLib CCPAlgorithms)
target_link_libraries(CCPRead ${QT_QTTEST_LIBRARY} CCPModelLib CCPIOLib CCPAlgorithms)
