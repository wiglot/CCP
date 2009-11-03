

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ../model)

set (CCPIO readccp.cpp)

qt4_automoc(${CCPIO})

add_library(CCPIOLib SHARED ${CCPIO})

target_link_libraries(CCPIOLib ${QT_QTCORE_LIBRARY} )