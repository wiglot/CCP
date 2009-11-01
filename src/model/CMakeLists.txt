
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})


set (Model_CCP Cluster.cpp Distance.cpp Instance.cpp Point.cpp Position.cpp Solution.cpp)

qt4_automoc(${Model_CCP})


add_library(CCPModelLib SHARED ${Model_CCP})

link_libraries(CCPModelLib ${QT_QT_LIBRARY})