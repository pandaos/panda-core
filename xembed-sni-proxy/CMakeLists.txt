project(panda-xembedsniproxy)

add_definitions(-DQT_NO_CAST_TO_ASCII
-DQT_NO_CAST_FROM_ASCII
-DQT_NO_URL_CAST_FROM_STRING
-DQT_NO_CAST_FROM_BYTEARRAY)

if (POLICY CMP0071)
  # We do not require the old behaviour. It is only set to old, to prevent accidential use of
  # the new behavour. If the new behaviour becomes important, cmake_minimum_required has to be
  # set to "3.10".
  cmake_policy(SET CMP0071 OLD) # Policy introduced in CMake version 3.10
endif()

find_package(XCB
    REQUIRED COMPONENTS
        XCB
        XFIXES
        DAMAGE
        COMPOSITE
        RANDR
        SHM
        UTIL
        IMAGE
)

find_package(KF5WindowSystem)

set(XCB_LIBS
    XCB::XCB
    XCB::XFIXES
    XCB::DAMAGE
    XCB::COMPOSITE
    XCB::RANDR
    XCB::SHM
    XCB::UTIL
    XCB::IMAGE
)

set(XEMBED_SNI_PROXY_SOURCES
    main.cpp
    fdoselectionmanager.cpp
    snidbus.cpp
    sniproxy.cpp
    xtestsender.cpp
)

qt5_add_dbus_adaptor(XEMBED_SNI_PROXY_SOURCES org.kde.StatusNotifierItem.xml
                     sniproxy.h SNIProxy)

set(statusnotifierwatcher_xml org.kde.StatusNotifierWatcher.xml)
qt5_add_dbus_interface(XEMBED_SNI_PROXY_SOURCES ${statusnotifierwatcher_xml} statusnotifierwatcher_interface)

add_executable(panda-xembedsniproxy ${XEMBED_SNI_PROXY_SOURCES})

set_package_properties(XCB PROPERTIES TYPE REQUIRED)

target_link_libraries(panda-xembedsniproxy
    Qt5::Core
    Qt5::X11Extras
    Qt5::DBus
    KF5::WindowSystem
    ${XCB_LIBS}
    ${X11_XTest_LIB}
)

install(TARGETS panda-xembedsniproxy DESTINATION /usr/bin)
