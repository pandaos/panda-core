project(panda-session)
set(TARGET panda-session)

find_package(KF5IdleTime)

file (GLOB_RECURSE SRCS
  "*.cpp"
  "*.h"
  "power/*.h"
  "power/*.cpp"
)

set(SOURCES ${SRCS})
set(HEADERS "")
set(FORMS "")
set(RESOURCES "")

qt5_add_dbus_adaptor(DBUS_SOURCES
                     org.panda.Session.xml
                     application.h Application)
set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${DBUS_SOURCES} ${FORMS} ${RESOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
        KF5::IdleTime
        )

install(TARGETS ${TARGET} DESTINATION /usr/bin)
install(FILES "panda-session.desktop" DESTINATION /usr/share/xsessions/)
