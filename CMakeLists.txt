cmake_minimum_required(VERSION 3.16.0)

project(todonext VERSION 1.0)

find_package(ECM 1.4.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 14)

# add 'make uninstall' target
include(ECMUninstallTarget)
# support '#include "todonextplugin.moc in file todonextplugin.cpp, else would got error "Failed to extract plugin meta data" when import in qml'
include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED NO_MODULE COMPONENTS
            Qml
            )
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS 
            Plasma
            )

add_subdirectory(todonext)

plasma_install_package(package com.suzakuwcx.todonext)