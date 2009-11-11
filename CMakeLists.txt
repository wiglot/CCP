project(CCP)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
enable_testing()

set(CMAKE_CXX_FLAGS "-g -Wall")


add_subdirectory(src)
add_subdirectory(tests)





