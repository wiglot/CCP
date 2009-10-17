project(CCP)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
enable_testing()

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(CCP_SRCS CCP.cpp main.cpp)
qt4_automoc(${CCP_SRCS})
add_executable(CCP ${CCP_SRCS})
target_link_libraries(CCP ${QT_QTCORE_LIBRARY})

add_subdirectory(tests)
