project(panda-policykit-agent)
include(GNUInstallDirs)

find_package(PkgConfig)
pkg_check_modules(POLKIT_AGENT REQUIRED polkit-agent-1)
message(STATUS "polkit agent: ${POLKIT_AGENT_INCLUDE_DIRS} ${POLKIT_AGENT_LIBRARIES}")

set(POLKIT_AGENT_BINARY_DIR "${CMAKE_INSTALL_BINDIR}" CACHE FILEPATH "Directory for install polkit agent")

find_package(Qt5Widgets REQUIRED)
find_package(PolkitQt5-1 REQUIRED)

# TODO/FIXME: pkg-config for hardcoded paths
# pkg-config --cflags glib-2.0
# pkg-config --cflags polkit-agent-1
include_directories(
    ${POLKIT_AGENT_INCLUDE_DIRS}
    "${POLKITQT-1_INCLUDE_DIR}"
)

set(SRCS
    main.cpp
    policykitagent.cpp
    policykitagentgui.cpp
)

add_executable(panda-policykit-agent
    ${SRCS}
)

target_link_libraries(panda-policykit-agent
    Qt5::Widgets
    ${POLKITQT-1_CORE_LIBRARY}
    ${POLKITQT-1_AGENT_LIBRARY}
    ${POLKIT_AGENT_LDFLAGS}
)

install(TARGETS panda-policykit-agent
    DESTINATION /usr/bin
    COMPONENT Runtime
)

install(FILES
    panda-policykit-agent.desktop
    DESTINATION "/etc/xdg/autostart"
    COMPONENT Runtime
)