cmake_minimum_required(VERSION 3.5)
project(panda-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT Core Gui Widgets DBus X11Extras)
find_package(Qt5 REQUIRED ${QT})
find_package(PkgConfig REQUIRED)

add_subdirectory(session)
add_subdirectory(shutdown)
add_subdirectory(policykit)
add_subdirectory(screen-brightness)
add_subdirectory(settings-daemon)
