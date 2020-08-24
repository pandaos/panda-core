cmake_minimum_required(VERSION 3.5)
project(panda-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT Core Gui Widgets DBus X11Extras)
find_package(Qt5 REQUIRED ${QT})
find_package(PkgConfig REQUIRED)
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(FeatureSummary)
include(WriteBasicConfigVersionFile)
include(GenerateExportHeader)

find_package(X11)
set_package_properties(X11 PROPERTIES DESCRIPTION "X11 libraries"
                        URL "http://www.x.org"
                        TYPE OPTIONAL
                        PURPOSE "Required for building the X11 based workspace")

if(X11_FOUND)
  find_package(XCB MODULE REQUIRED COMPONENTS XCB RANDR)
  set_package_properties(XCB PROPERTIES TYPE REQUIRED)
  if(NOT X11_SM_FOUND)
    message(FATAL_ERROR "\nThe X11 Session Management (SM) development package could not be found.\nPlease install libSM.\n")
  endif(NOT X11_SM_FOUND)

  find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS X11Extras)
endif()

if(X11_FOUND AND XCB_XCB_FOUND)
  set(HAVE_X11 1)
endif()

add_subdirectory(session)
add_subdirectory(shutdown)
add_subdirectory(policykit)
add_subdirectory(screen-brightness)
add_subdirectory(settings-daemon)
add_subdirectory(xembed-sni-proxy)
