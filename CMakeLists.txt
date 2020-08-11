cmake_minimum_required(VERSION 3.5)
project(panda-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT Core Gui Widgets DBus)
find_package(Qt5 REQUIRED ${QT})
find_package(PkgConfig REQUIRED)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

add_subdirectory(session)
add_subdirectory(shutdown)
add_subdirectory(policykit)
add_subdirectory(settings-daemon)
