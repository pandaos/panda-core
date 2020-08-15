project(panda-settings-daemon)
set(TARGET panda-settings-daemon)

find_package(PulseAudio)

file (GLOB_RECURSE SRCS
  "*.cpp"
  "*.h"
  "audio/*.cpp"
  "audio/*.h"
  "theme/*.h"
  "theme/*.cpp"
  "brightness/*.h"
  "brightness/*.cpp"
  "brightness/*.c"
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
        Qt5::X11Extras
        ${PULSEAUDIO_LIBRARY}
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)
