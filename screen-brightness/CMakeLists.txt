project(panda-screen-brightness)
set(PROJECT_NAME panda-screen-brightness)

set(SRCS
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${SRCS}
)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
install(FILES org.panda.brightness.pkexec.policy DESTINATION /usr/share/polkit-1/actions/)
