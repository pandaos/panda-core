project(panda-session)
set(TARGET panda-session)

find_package(KF5 REQUIRED COMPONENTS IdleTime)

file (GLOB_RECURSE SRCS
  "src/*.cpp"
  "src/*.h"
  "src/power/*.h"
  "src/power/*.cpp"
)

set(SOURCES ${SRCS})
set(HEADERS "")
set(FORMS "")
set(RESOURCES "")

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
        KF5::IdleTime
        )

install(TARGETS ${TARGET} DESTINATION /usr/bin)
install(FILES "panda-session.desktop" DESTINATION /usr/share/xsessions/)
