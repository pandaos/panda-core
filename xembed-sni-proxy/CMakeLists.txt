project(panda-xembedsniproxy)

add_definitions(-DQT_NO_CAST_TO_ASCII
-DQT_NO_CAST_FROM_ASCII
-DQT_NO_URL_CAST_FROM_STRING
-DQT_NO_CAST_FROM_BYTEARRAY)

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

qt5_add_dbus_adaptor(DBUS_SOURCES org.kde.StatusNotifierItem.xml
                     sniproxy.h SNIProxy)
set(statusnotifierwatcher_xml org.kde.StatusNotifierWatcher.xml)
qt5_add_dbus_interface(DBUS_SOURCES ${statusnotifierwatcher_xml} statusnotifierwatcher_interface)

set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(panda-xembedsniproxy ${XEMBED_SNI_PROXY_SOURCES} ${DBUS_SOURCES})
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
