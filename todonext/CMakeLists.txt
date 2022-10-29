set(PLUGIN_NAME todonext)

set(PLUGIN_SRC
    todonextplugin.cpp
    task.cpp
    todonext.cpp
    abstracttask.h
    )

add_library(${PLUGIN_NAME} SHARED ${PLUGIN_SRC})
target_link_libraries(${PLUGIN_NAME}
                    Qt5::Qml
                    )

install(TARGETS ${PLUGIN_NAME} DESTINATION ${KDE_INSTALL_QMLDIR}/com/suzakuwcx/todonextplugin)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/com/suzakuwcx/todonextplugin)