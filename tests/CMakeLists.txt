
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CCPTest_SRCS CCPTest.cpp)
qt4_automoc(${CCPTest_SRCS})
add_executable(CCPTest ${CCPTest_SRCS})
add_test(CCPTest CCPTest)
target_link_libraries(CCPTest ${QT_QTTEST_LIBRARY})
