include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )
include_directories( /usr/include/rocs )

Set ( DATFilePlugin_SRC DATFilePlugin.cpp )


kde4_add_plugin( datfileplugin ${DATFilePlugin_SRC} )
target_link_libraries(datfileplugin
			    ${KDE4_KDEUI_LIBS}
                            rocslib
)

install(TARGETS datfileplugin  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES datfileplugin.desktop  DESTINATION ${SERVICES_INSTALL_DIR})
