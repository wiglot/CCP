

add_subdirectory(model)
add_subdirectory(io)
add_subdirectory(algorithms)
add_subdirectory(gui)


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} model io)

set(CCP_SRCS main.cpp model/Distance.cpp model/Instance.cpp model/Point.cpp model/Position.cpp model/Solution.cpp model/Cluster.cpp)
qt4_automoc(${CCP_SRCS})
add_executable(CCP main.cpp )

target_link_libraries(CCP ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} CCPModelLib CCPIOLib CCPAlgorithms CCPClusterView) 

