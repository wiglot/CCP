project(CCP)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)


set(CMAKE_CXX_FLAGS "-g -Wall")


add_subdirectory(src)
IF(TESTS)
	enable_testing()
	add_subdirectory(tests)
ENDIF(TESTS)




