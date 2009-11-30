

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../model)

set(SRC_view viewcluster.cpp)
set(SRC_view_H viewcluster.h)

qt4_automoc(${SRC_view})
QT4_WRAP_CPP(MOC_CPP ${SRC_view_H})
add_library(CCPClusterView SHARED ${SRC_view} ${MOC_CPP})

target_link_libraries(CCPClusterView ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} CCPModelLib)