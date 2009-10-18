

add_subdirectory(model)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} model)

set(CCP_SRCS  main.cpp)
qt4_automoc(${CCP_SRCS})
add_executable(CCP ${CCP_SRCS})

target_link_libraries(CCP ${QT_QTCORE_LIBRARY} ${CCP_Model})