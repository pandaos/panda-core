project(panda-shutdown)
set(TARGET panda-shutdown)

set(SRCS main.cpp
         powermanager.cpp
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
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)