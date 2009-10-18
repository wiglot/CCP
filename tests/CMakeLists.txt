
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../src/model)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CCPTest_SRCS CCPTest.cpp)
set(CCPModel_SRCS ccpmodel_test.cpp)

qt4_automoc(${CCPTest_SRCS})
qt4_automoc(${CCPModel_SRCS})

add_executable(CCPTest ${CCPTest_SRCS})
add_executable(CCPModel ${CCPModel_SRCS})

add_test(CCPTest CCPTest)
add_test(CCPModel CCPModel)

target_link_libraries(CCPTest ${QT_QTTEST_LIBRARY})
target_link_libraries(CCPModel ${QT_QTTEST_LIBRARY})